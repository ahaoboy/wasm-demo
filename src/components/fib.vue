<template>
  <div></div>
</template>

<script>
import wasm from "./fibArray";
import url from "./fibArray.wasm";
console.log("url", url);
console.log("wasm", wasm);
wasm().then((wasmModule) => {
  console.log("data", wasmModule);
  for (let i = 0; i < 10; i++) {
    console.log("fib", i, wasmModule._fib(i));
  }

  const fib = wasmModule["_fib"];
  for (let i = 0; i < 10; i++) {
    console.log("fib", i, fib(i));
  }

  const size = 10;
  const ccall = wasmModule.ccall;
  const bufferIntArray = Array(size)
    .fill()
    .map((_, i) => i);
  const numBytes = Int32Array.BYTES_PER_ELEMENT * size;
  const ptr = wasmModule._malloc(numBytes);
  const heapBytes = new Uint32Array(wasmModule.HEAP32.buffer, ptr, numBytes);
  heapBytes.set(new Int32Array(bufferIntArray));
  const resultPtr = ccall(
    "fibArray",
    "Int32Array",
    ["Int32Array", "number"],
    [heapBytes.byteOffset, size]
  );
  console.log("resultPtr", resultPtr);
  const resultArray = new Int32Array(wasmModule.HEAP32.buffer, resultPtr, size);
  console.log("resultArray", resultArray);
  console.log("raw", new Int32Array(wasmModule.HEAP32.buffer, ptr, size));
});

// wasmModule.onRuntimeInitialized(()=>{
//     console.log('===',wasmModule)
// })
export default {};
</script>

<style></style>
