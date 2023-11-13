#include "tensorflow/core/public/session.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/graph/graph.h"
#include "tensorflow/core/graph/node_builder.h"
#include "tensorflow/core/framework/function.h"
#include "tensorflow/core/public/version.h"
#include <thread>  // NOLINT
#include <memory>
#include <atomic>
using namespace tensorflow;
using namespace std;
typedef FunctionDefHelper FDH;

atomic_int64_t counter;
class TestClass{
public:
  TestClass(int a_, int b_, float c_): a(a_), b(b_), c(c_)
  {
    counter.fetch_add(1);
    i_ptr = (int*)malloc(512*1024);
  }
  ~TestClass()
  {
    counter.fetch_sub(1);
    std::string str = "~TestClas" + std::to_string(counter.load());
    std::cout << str << std::endl;
    delete i_ptr;
  }

  int a;
  int b;
  float c;
  int* i_ptr;
};
Node* Constant(Graph* g, const Tensor& tensor) {
  Node* ret;
  TF_CHECK_OK(NodeBuilder(g->NewName("n"), "Const")
                  .Attr("dtype", tensor.dtype())
                  .Attr("value", tensor)
                  .Finalize(g, &ret));
  return ret;
}

Node* Binary(Graph* g, const string& func, Node* in0, Node* in1) {
  Node* ret;
  TF_CHECK_OK(NodeBuilder(g->NewName("n"), func, g->op_registry())
                  .Input(in0)
                  .Input(in1)
                  .Finalize(g, &ret));
  return ret;
}

Node* Unary(Graph* g, const string& func, Node* input, int index = 0) {
  Node* ret;
  TF_CHECK_OK(NodeBuilder(g->NewName("n"), func, g->op_registry())
                  .Input(input, index)
                  .Finalize(g, &ret));
  return ret;
}

REGISTER_OP("SessionMetadataReader")
    .Input("x: uint64")
    .Output("y: string")
    .SetIsStateful();

class SessionMetadataReaderOp : public OpKernel {
 public:
  explicit SessionMetadataReaderOp(OpKernelConstruction* ctx) : OpKernel(ctx) {}
  void Compute(OpKernelContext* ctx) override {
    const Tensor& a = ctx->input(0);
    unique_ptr<TestClass> a_ptr(const_cast<TestClass*>(a.scalar<TestClass*>()()));
    // auto a_ptr = a.scalar<TestClass*>()();

    Tensor* out_tensor = nullptr;
    OP_REQUIRES_OK(ctx,
                   ctx->allocate_output("y", TensorShape({}), &out_tensor));
    out_tensor->scalar<tstring>()() = std::to_string(a_ptr->c);
  }
};
REGISTER_KERNEL_BUILDER(Name("SessionMetadataReader").Device(DEVICE_CPU),
                        SessionMetadataReaderOp);
REGISTER_KERNEL_BUILDER(Name("SessionMetadataReader").Device(DEVICE_GPU),
                        SessionMetadataReaderOp);

REGISTER_OP("BinaryReader")
    .Input("x1: int64")
    .Input("y: string")
    .Output("a: string")
    .Output("b: uint64");

class BinaryReaderOp : public OpKernel {
 public:
  explicit BinaryReaderOp(OpKernelConstruction* ctx) : OpKernel(ctx) {}
  void Compute(OpKernelContext* ctx) override {
    // Grab the input tensor
    const Tensor& x1 = ctx->input(0);
    auto X1 = x1.flat<int64>();
    const Tensor& y = ctx->input(1);
    auto Y = y.flat<string>();
    
    // Create an output tensor
    Tensor* out_tensor1 = nullptr;
    OP_REQUIRES_OK(ctx, ctx->allocate_output("a", y.shape(), &out_tensor1));
    Tensor* out_tensor2 = NULL;
    OP_REQUIRES_OK(ctx, ctx->allocate_output("b", x1.shape(), &out_tensor2));

    out_tensor1->scalar<tstring>().setConstant(*(Y.data()));
    // out_tensor1->scalar<tstring>()() = y.tensor_data().data();

    out_tensor2->scalar<uint64>()() = (uint64)(new TestClass(1,2,3.4));
  }
};
REGISTER_KERNEL_BUILDER(Name("BinaryReader").Device(DEVICE_CPU),
                        BinaryReaderOp);
REGISTER_KERNEL_BUILDER(Name("BinaryReader").Device(DEVICE_GPU),
                        BinaryReaderOp);

// FunctionDef SessionMetadataReaderOpFn() {
//   return FunctionDefHelper::Define(
//       // Name
//       "SessionMetadataReaderFn",
//       // Args
//       {"x: int64"},
//       // Return values
//       {"y: string"},
//       // Attr def
//       {},
//       // Nodes
//       {{{"y"}, "SessionMetadataReader", {"x"}, {}}});
// }


// GraphDef GDef(gtl::ArraySlice<NodeDef> nodes,
//               gtl::ArraySlice<FunctionDef> funcs) {
//   GraphDef g;
//   VersionDef* versions = g.mutable_versions();
//   versions->set_producer(TF_GRAPH_DEF_VERSION);
//   versions->set_min_consumer(TF_GRAPH_DEF_VERSION_MIN_CONSUMER);
//   for (const auto& n : nodes) {
//     *(g.add_node()) = n;
//   }
//   auto lib = g.mutable_library();
//   for (const auto& f : funcs) {
//     *(lib->add_function()) = f;
//   }
//   return g;
// }

SessionOptions DefaultSessionOptions() {
  SessionOptions options;
//   (*options.config.mutable_device_count())["CPU"] = 2;
  return options;
}
std::unique_ptr<Session> CreateSession() {
  return std::unique_ptr<Session>(NewSession(DefaultSessionOptions()));
}

// int test_op_lib() {
// 	FunctionDefLibrary library_graph_def;
// 	*library_graph_def.add_function() = SessionMetadataReaderOpFn();
// 	FunctionLibraryDefinition flib(OpRegistry::Global(), library_graph_def);

// 	Graph g(&flib);
// 	Tensor vx(DT_INT64, TensorShape({}));
// 	vx.scalar<int64>()() = 17;
// 	Node* x = Constant(&g, vx);
// 	Node* y = Unary(&g, "SessionMetadataReader", x);
// 	GraphDef def;
// 	g.ToGraphDef(&def);
// 	*def.mutable_library() = library_graph_def;

// 	auto sess = CreateSession();
// 	sess->Create(def);
// 	std::vector<Tensor> outputs;
// 	RunOptions run_opts;
// 	run_opts.set_inter_op_thread_pool(-1);
// 	auto status = sess->Run(run_opts, {}, {y->name() + ":0"}, {}, &outputs, nullptr);

// 	if (!status.ok()) {
// 	std::cout <<"haha"<<std::endl;
// 	std::cout << status.ToString() << "\n";
// 	std::cout <<"hehe"<<std::endl;
// 	return 1;
// 	}

// 	// Grab the first output (we only evaluated one graph node: "c")
// 	// and convert the node to a scalar representation.
// 	auto output_c = outputs[0];
// 	std::cout <<"123"<<std::endl;

// 	// (There are similar methods for vectors and matrices here:
// 	// https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/public/tensor.h)

// 	// Print the results
// 	std::cout << outputs[0].DebugString() << "\n"; // Tensor<type: float shape: [] values: 30>
// 	//std::cout << output_c() << "\n"; // 30
// 	return 0;
// }

void test_op() {
	Graph g(OpRegistry::Global());
	Tensor vx(DT_UINT64, TensorShape({}));
	vx.scalar<TestClass*>()() = new TestClass(1, 2, 3.0);
	Node* x = Constant(&g, vx);
	Node* y = Unary(&g, "SessionMetadataReader", x);
  Tensor vx1(DT_INT64, TensorShape({}));
	vx1.scalar<int64>()() = 17;
	Node* x1 = Constant(&g, vx1);
  Node* y2 = Binary(&g, "BinaryReader", x1, y);
	GraphDef def;
	g.ToGraphDef(&def);
	auto sess = CreateSession();
	sess->Create(def);
	std::vector<Tensor> outputs;
	RunOptions run_opts;
	// run_opts.set_inter_op_thread_pool(-1);
	auto s = sess->Run(run_opts, {}, {y2->name() + ":0", y2->name() + ":1"}, {}, &outputs, nullptr);
	// std::cout << outputs.size() << "\n"; 
  // std::cout << outputs[0].DebugString() << "\n"; 
  TestClass* p = (TestClass*)(outputs[1].flat<uint64>()(0));
	// std::cout << (*p).a << "\t" << (*p).b << "\t" << (*p).c  << "\n";
  delete p;
}


int main(int argc, char* argv[]) {
  counter.store(0);
  for(int i = 0; i < 100000000; i++) {
	  test_op();
  }
	return 0;
}