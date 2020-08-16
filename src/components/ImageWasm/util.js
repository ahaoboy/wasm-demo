function fillWasm(data, x, y, w, h) {
  const size = data.length;
  const ccall = Module.ccall;
  const numBytes = size * Uint8Array.BYTES_PER_ELEMENT;
  const ptr = Module._malloc(numBytes);
  const heapBytes = new Uint8Array(Module.HEAP8.buffer, ptr, numBytes);
  const imageDataBuffer = Uint8Array.from(data);
  heapBytes.set(new Uint8Array(imageDataBuffer));
  const st = +new Date();
  ccall(
    "fillWasm",
    "null",
    ["Uint8Array", "number", "number", "number", "number"],
    [heapBytes.byteOffset, x, y, w, h]
  );
  console.log("time wasm:", +new Date() - st);
  const resultArray = new Uint8Array(Module.HEAP8.buffer, ptr, size);
  const result = new Uint8ClampedArray(resultArray);
  return result
}
// console.log(wasmModule)
export const delColor = (canvas, x, y) => {
  const w = canvas.width;
  const h = canvas.height;
  const ctx = canvas.getContext("2d");
  const { data, width, height } = ctx.getImageData(0, 0, w, h);
  const newData = fillWasm(data, x, y, width, height);
  const b2 = new ImageData(newData, width, height);
  ctx.putImageData(b2, 0, 0);
};
