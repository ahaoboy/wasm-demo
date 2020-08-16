const path = require("path");
const { VueLoaderPlugin } = require("vue-loader");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");

module.exports = (env = {}) => ({
  mode: env.prod ? "production" : "development",
  devtool: env.prod ? "source-map" : "cheap-module-eval-source-map",
  entry: path.resolve(__dirname, "./src/main.js"),
  node: {
    fs: "empty", // ← !!
    __dirname: false,
    Buffer: false,
    process: false,
  },
  output: {
    path: path.resolve(__dirname, "./dist"),
    publicPath: "/dist/",
  },
  // experiments: {
  //   asyncWebAssembly: true,
  // },
  resolve: {
    alias: {
      // this isn't technically needed, since the default `vue` entry for bundlers
      // is a simple `export * from '@vue/runtime-dom`. However having this
      // extra re-export somehow causes webpack to always invalidate the module
      // on the first HMR update and causes the page to reload.
      vue: "@vue/runtime-dom",
    },
    extensions: [".js", ".jsx", ".vue"],
  },
  module: {
    rules: [
      {
        test: /\.vue$/,
        use: "vue-loader",
      },
      {
        test: /\.(png|jpg|gif|svg)$/,
        use: {
          loader: "url-loader",
          options: { limit: 8192 },
        },
      },
      // {
      //   test: /\.wasm$/,
      //   loaders: ["wasm-loader"],
      // },
      {
        test: /\.wasm$/,
        type: "javascript/auto",
        use: {
          loader: "url-loader",
          options: { limit: 8192, name: "[name].[ext]" },
        },
      },
      // {
      //   test: /\.css$/,
      //   use: [
      //     {
      //       loader: MiniCssExtractPlugin.loader,
      //       options: { hmr: !env.prod }
      //     },
      //     'css-loader'
      //   ]
      // }
      {
        test: /\.js$/,
        loader: require.resolve("@open-wc/webpack-import-meta-loader"),
      },
      {
        test: /\.css|\.less$/,
        use: [
          "style-loader",
          {
            loader: MiniCssExtractPlugin.loader,
            options: { hmr: !env.prod },
          },
          "css-loader",
          "less-loader",
        ],
      },
    ],
  },
  plugins: [
    new VueLoaderPlugin(),
    new MiniCssExtractPlugin({
      filename: "[name].css",
    }),
  ],
  devServer: {
    inline: true,
    hot: true,
    stats: "minimal",
    contentBase: __dirname,
    overlay: true,
  },
});
