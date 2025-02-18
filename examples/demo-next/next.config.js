/* eslint-disable */
const withCss = require('@zeit/next-css')
// fix: prevents error when .css files are required by node
if (typeof require !== 'undefined') {
  require.extensions['.css'] = file => {}
}
const { useStaticRendering} = require('mobx-react');
if (process.env.SSR) {
  useStaticRendering(true);
}
let options = withCss({
  webpack: (config, { isServer }) => {
    // if (isServer) {
    //   const antStyles = /(antd\/.*?\/style\/css.*?)|(antd-mobile\/.*?\/style.*?)/
    //   const origExternals = [...config.externals]
    //   config.externals = [
    //     (context, request, callback) => {
    //       if (request.match(antStyles)) return callback()
    //       if (typeof origExternals[0] === 'function') {
    //         origExternals[0](context, request, callback)
    //       } else {
    //         callback()
    //       }
    //     },
    //     ...(typeof origExternals[0] === 'function' ? [] : origExternals),
    //   ]

    //   config.module.rules.unshift({
    //     test: antStyles,
    //     use: 'null-loader',
    //   })
    // }
    return config
  },
})

module.exports = {
  ...options,
}
