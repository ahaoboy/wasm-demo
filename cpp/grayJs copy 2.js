// 图片太大会OOM
const imgPath = "./t2.jpg";

Module.onRuntimeInitialized = async () => {
  console.log("Module", Module);
  const grayCpp = Module.grayCpp;
  const create_buffer = Module.create_buffer;
  const imgBlob = await fetch(imgPath).then((resp) => resp.blob());
  const blobURL = URL.createObjectURL(imgBlob);
  const img = document.createElement("img");
  img.src = blobURL;
  document.body.appendChild(img);
  img.onload = () => {
    const canvas = document.createElement("canvas");
    canvas.width = img.width;
    canvas.height = img.height;
    document.body.appendChild(canvas);
    const ctx = canvas.getContext("2d");
    ctx.drawImage(img, 0, 0);
    const data = ctx.getImageData(0, 0, img.width, img.height);
    console.log('data',data,data.width, data.height)
    const p =  create_buffer(data.width, data.height);
    console.log('p',p)
    Module.HEAP8.set(data.data, p);
    const grayPointer = grayCpp(p, data.width, data.height, 75);
    const imageData = new Uint8Array(Module.HEAP8.buffer, grayPointer, data.width * data.height * 4);
    const blob = new Blob([imageData], { type: "image/jpg" });
    const blobURL = URL.createObjectURL(blob);
    const img2 = document.createElement("img");
    img2.src = blobURL;
    document.body.appendChild(img2);
  };
};
