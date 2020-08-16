<template>
  <div class="wrap">
    <img
      @click="clickInput"
      class="box"
      ref="inputRef"
      :src="imageUrl"
      alt=""
    />
    <canvas :style="canvasStyleRef" ref="canvasRef" class="box"></canvas>
    <img :style="canvasStyleRef" ref="outputRef" class="box" src="" alt="" />
  </div>
</template>

<script>
import { ref, onMounted } from "vue";
import { delColor } from "./util";
export default {
    props:['imageUrl'],
  setup(props) {
    console.log("props", props);
    const imageUrl = ref(props.imageUrl);
    const canvasRef = ref(null);
    const outputRef = ref(null);
    const inputRef = ref(null);
    const canvasStyleRef = ref("");
    // 将图片绘制到canvas中
    const input = () => {
      if (!inputRef.value || !canvasRef.value) return;
      console.log("input");
      canvasRef.value
        .getContext("2d")
        .drawImage(
          inputRef.value,
          0,
          0,
          inputRef.value.width,
          inputRef.value.height
        );
    };

    // 将canvas中的内容画到图片中
    const output = () => {
      if (!outputRef.value || !canvasRef.value) return;
      console.log("output");
      const url = canvasRef.value.toDataURL("image/png", 1);
      outputRef.value.src = url;
    };

    onMounted(() => {
      inputRef.value.onload = () => {
        // const { width, height } = inputRef.value.getBoundingClientRect();
        canvasRef.value.width = inputRef.value.width;
        canvasRef.value.height = inputRef.value.height;
        // canvasRef.value.height =  width;
        // canvasRef.value.height =  height;
        input();
        output();
        console.log(inputRef.value.width);
        canvasStyleRef.value = `width:${canvasRef.width}px;height:${canvasRef.height}px`;
      };
    });

    const clickInput = (e) => {
      console.log(e);
      const x = e.offsetX;
      const y = e.offsetY;
      const color = canvasRef.value.getContext("2d").getImageData(x, y, 1, 1)
        .data;
      delColor(canvasRef.value, x, y, color);
      output();
    };
    return {
      clickInput,
      canvasRef,
      canvasStyleRef,
      inputRef,
      outputRef,
      imageUrl,
    };
  },
};
</script>

<style lang="less">
.wrap {
  display: flex;
  align-items: center;
  justify-content: space-around;
  width: 100%;
  height: 100%;

  .box {
    //   width: 100%;
    // width: 25%;
    // height: auto;
  }
}
</style>
