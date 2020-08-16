const Module = require('./a.out')
const fs = require('fs')
var pixels = require('image-pixels')

// 图片太大会OOM
// const imgPath = './s.jpg'
const imgPath = './s3.jpg'

async function getImageData() {
    return pixels(imgPath)
}

Module.onRuntimeInitialized = async () => {
    console.log("Module",Module['grayCpp'])
    
    // const api = {
    //     version: Module.cwrap('version', 'number', []),
    //     create_buffer: Module.cwrap('create_buffer', 'number', ['number', 'number']),
    //     destroy_buffer: Module.cwrap('destroy_buffer', '', ['number']),
    //     encode: Module.cwrap('encode', '', ['number', 'number', 'number', 'number']),
    //     free_result: Module.cwrap('free_result', '', ['number']),
    //     get_result_pointer: Module.cwrap('get_result_pointer', 'number', []),
    //     get_result_size: Module.cwrap('get_result_size', 'number', []),
    // };
    // console.log(api.version());
    // const {data, width, height} = await getImageData()
    // const q = 75

    // const st1 = +new Date()
    // const p = api.create_buffer(width, height);
    // Module.HEAP8.set(data, p);
    // api.encode(p, width, height, q);
    // console.log("time1:", +new Date() - st1)
    // const resultPointer = api.get_result_pointer();
    // const resultSize = api.get_result_size();
    // console.log("time12:", +new Date() - st1)
    // console.log(resultPointer, resultSize)
    // const resultView = new Uint8Array(Module.HEAP8.buffer, resultPointer, resultSize);
    // const result = new Uint8Array(resultView);
    // console.log("time123:", +new Date() - st1)
    // console.log(result.length / 1024)
    // // console.log("time1:", +new Date() - st1)
    // // const blob = new Blob([result], {type: 'image/webp'});
    // api.destroy_buffer(p);


    // const jsOutPath = './js-out' + (+new Date()) + '.webp'
    // const st2 = +new Date()
    // const result2 = await webp.cwebp(imgPath, jsOutPath, `-q ${q}`);
    // console.log('time2:', +new Date() - st2)
}