const wasmModule = require("./a.out");

wasmModule.onRuntimeInitialized = async () => {
  const fib = wasmModule["_fib"];
  for (let i = 0; i < 10; i++) {
    console.log("fib", i, fib(i));
  }

  const ccall = wasmModule.ccall
  
};
