const setColor = (data, x, y, w, c) => {
  for (let dx = 0; dx < c.length; dx++) {
    data[(y * w + x) * 4 + dx] = c[dx];
  }
};

const getColor = (data, x, y, w) => {
  return data.slice((y * w + x) * 4, (y * w + x) * 4 + 4);
};

Array.prototype.top = function () {
  return this[this.length - 1];
};

const abs = (a) => (a < 0 ? -a : a);
// 返回值为真, 表示颜色相似
const compare = ([r1, g1, b1], [r2, g2, b2]) => {
  // const d1 = r1 ** 2 + g1 ** 2 + b1 ** 2;
  // const d2 = r2 ** 2 + g2 ** 2 + b2 ** 2;
  // const a = (r1 * r2 + g1 * g2 + b1 * b2) / (d1 ** 0.5 * d2 ** 0.5);
  // if (isNaN(a)) {
  //   return false;
  // }
  // return a > 0.9;

  const d = abs(r1 - r2) + abs(b1 - b2) + abs(g1 - g2);
  return 1 - d / 255 / 3 > 0.9;
  // return d < 255;
};

// 泛洪填充,第一个是一维颜色数组rgba, 开始坐标, 填充的颜色
// 返回新数组
const fillJS = (data, x, y, w, h) => {
  const a = Uint8ClampedArray.from(data);
  const sourceColor = getColor(data, x, y, w);
  const fillColor = [98, 237, 240, 255];
  console.log("fill", x, y, w, h, sourceColor);

  // 是否已经访问过
  const v = {};

  const canVisit = (_x, _y) => {
    // console.log("canVisit", _x, _y, v);
    // 超界不能访问
    if (_x < 0 || _y < 0 || _x >= w || _y >= h) return false;
    return !v[(_x << 16) + _y];
    // return !v[_x + "," + _y];
  };

  const setVisit = (_x, _y, value) => {
    v[(_x << 16) + _y] = value;
    // v[_x + "," + _y] = value;
  };

  // 按照上下左右, 还是八宫格
  const direction = [
    [0, 1],
    [0, -1],
    [-1, 0],
    [1, 0],
    // [1, 1],
    // [1, -1],
    // [-1, 1],
    // [-1, -1],
  ];

  // 位置和方向
  const stack = [[x, y, 0]];
  let count = 0;
  const visit = (x, y) => {
    setColor(a, x, y, w, fillColor);
  };

  while (stack.length) {
    count++;
    const top = stack.top();
    const [tx, ty, td] = top;
    // console.log("top", tx, ty, stack.length);
    // 访问, 并设置已经访问过了
    visit(tx, ty);
    setVisit(tx, ty, true);
    if (td === direction.length) {
      stack.pop();
      continue;
    }
    const [dx, dy] = direction[td];
    const nx = tx + dx;
    const ny = ty + dy;
    top[2] = td + 1;
    if (canVisit(nx, ny) && compare(sourceColor, getColor(data, nx, ny, w))) {
      stack.push([nx, ny, 0]);
      setVisit(tx, ty, true);
    } else if (
      nx >= 0 &&
      ny >= 0 &&
      nx < w &&
      ny < h &&
      !compare(sourceColor, getColor(data, nx, ny, w))
    ) {
      setColor(a, nx, ny, w, [255, 0, 0, 255]);
    }
  }
  console.log("count", count);
  return a;
};

const sleep = (time = 1000) => {
  return new Promise((resove) => setTimeout(() => resove(), time));
};

const fillWASM = () => {};

export const delColor = (canvas, x, y) => {
  const w = canvas.width;
  const h = canvas.height;
  const ctx = canvas.getContext("2d");
  const { data, width, height } = ctx.getImageData(0, 0, w, h);
  const st = +new Date();
  const newData = fillJS(data, x, y, width, height);
  console.log("time js:", +new Date() - st);
  const b2 = new ImageData(newData, width, height);
  ctx.putImageData(b2, 0, 0);
};
