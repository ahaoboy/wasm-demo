<template>
  <div>
    <div>
      <ImageJs  :imageUrl='imageUrlRef'/>
    </div>
    <div>
      <ImageWasm :imageUrl='imageUrlRef' />
    </div>
  </div>
</template>

<script>
import ImageJs from "./components/ImageJS";
import ImageWasm from "./components/ImageWasm";
import imageUrl from "./images/t-big2.png";
import {ref} from 'vue'

const components = { ImageJs, ImageWasm };
export default {
  components,
  setup() {
    const imageUrlRef = ref(imageUrl);
    console.log("imageUrl", imageUrl);
    return {
      imageUrlRef,
    };
  },
};
</script>

<style scoped></style>
