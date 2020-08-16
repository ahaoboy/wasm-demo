const wasmModule = require('./a.out')

wasmModule.onRuntimeInitialized = async () => {
    console.log('module',wasmModule.cwrap('f1',"object",[])())
}