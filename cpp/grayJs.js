let imageData
let w
let h
const input = document.getElementById('input')
const canvas = document.createElement('canvas')
const output = document.createElement('canvas')
input.onload = () => {
    w = input.width
    h = input.height
    canvas.width = output.width = w
    canvas.height = output.height = h
    const ctx = canvas.getContext('2d')
    ctx.drawImage(input, 0, 0)
    document.body.append(canvas)
    imageData = ctx.getImageData(0, 0, w, h)
}

Module.onRuntimeInitialized = () => {
    console.log('===', imageData, w, h)
    console.log('wasm', Module)

    // const st = +new Date()
    //
    //
    // grayJs(imageData.data, w, h)
    // console.log('time:', +new Date() - st, imageData.data.length)
    // console.log(imageData)
    //
    // output.getContext('2d').putImageData(imageData, 0, 0)
    // document.body.append(output)
}

function test() {

    const api = {
        create_buffer: Module.cwrap('create_buffer', 'number', ['number', 'number']),
        grayCpp: Module.cwrap('grayCpp', '', ['number', 'number', 'number', 'number']),
    };

    const p = api.create_buffer(w, h);
    console.log(imageData.data.length)
    Module.HEAP8.set(imageData.data, p);
    const st = +new Date()
    api.grayCpp(p, w, h);
    console.log('time:', +new Date() - st)
    const resultView = new Uint8Array(Module.HEAP8.buffer, p, w * h * 4);
    const result = new Uint8ClampedArray(resultView);
    console.log('result', result.length)

    const outputData = new ImageData(result, w, h)
    output.getContext('2d').putImageData(outputData, 0, 0)
    document.body.append(output)
}

document.addEventListener('click', test)