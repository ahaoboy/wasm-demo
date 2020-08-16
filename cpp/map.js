const wasmModule = require("./a.out");

wasmModule.onRuntimeInitialized = async () => {
  console.log(wasmModule["returnVectorData"]());
  let retVector = wasmModule["returnVectorData"]();
  let vectorSize = retVector.size();
  retVector.set(vectorSize - 1, 11);
  retVector.push_back(12);
  for (let i = 0; i < retVector.size(); i++) {
    console.log("Vector Value: ", retVector.get(i));
  }
  retVector.resize(20, 1);
  console.log("retVector.size()",retVector.size())
  let retMap = wasmModule["returnMapData"]();

  let mapSize = retMap.size();
  console.log("mapSize", mapSize);
  console.log("Map Value: ", retMap.get(10));

  // to make vectors available
  let mapKeys = retMap.keys();
  for (let i = 0; i < mapKeys.size(); i++) {
    let key = mapKeys.get(i);
    console.log("Map key/value: ", key, retMap.get(key));
  }

  // reset the value at the given index position
  retMap.set(10, "OtherValue");
};
