const wasmModule = require("./a.out");

wasmModule.onRuntimeInitialized = async () => {
  console.log(wasmModule.cwrap, wasmModule.ccall);
  const ccall = wasmModule.ccall;
  const inc = wasmModule["_inc"];
  const createIntArray = wasmModule["_createIntArray"];
  
  console.log("inc", inc);
  console.log("createIntArray", createIntArray);
  const size = 5;
  const p = createIntArray(10);
  console.log("p", p);

  const resultView = new Int32Array(wasmModule.HEAP32.buffer, p, size);
  resultView[0] = 111;
  console.log("resultView", resultView);
  const result = new Int32Array(resultView);
  result[1] = 222;
  console.log("result", result);

  for (let i = 0; i < size; i++) {
    result[i] = i;
  }
  console.log("result", result);
  const p2 = inc(result, size);
  console.log("p2", p2);
  const resultView2 = new Int32Array(wasmModule.HEAP32.buffer, p2, size);
  console.log("resultView2", resultView2);

  const bufferIntArray = Array(size)
    .fill()
    .map((_, i) => i);
  const numBytes = Int32Array.BYTES_PER_ELEMENT * size;
  const ptr = wasmModule._malloc(numBytes);
  const heapBytes = new Uint32Array(wasmModule.HEAP32.buffer, ptr, numBytes);
  heapBytes.set(new Int32Array(bufferIntArray));
  const pp = ccall(
    "inc",
    "Int32Array",
    ["Int32Array", "number"],
    [heapBytes.byteOffset, size]
  );
  console.log("pp", pp);
  const resultView22 = new Int32Array(wasmModule.HEAP32.buffer, pp, size);
  console.log("resultView2", resultView22);

  //   Module.HEAP32.set(new Int32Array())
};
