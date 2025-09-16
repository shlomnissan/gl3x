import { defineConfig } from 'vitepress'

const year = new Date().getFullYear();

export default defineConfig({
  srcDir: 'pages',
  title: 'Gleam',
  description: '3D Rendering in Modern C++',
  head: [
    ['link', { rel: 'stylesheet', href: 'https://use.typekit.net/twl6gwz.css' }]
  ],
  cleanUrls: true,
  themeConfig: {
    logo: {
      light: '/logo-light.svg',
      dark: '/logo-dark.svg'
    },
    nav: [
      { text: 'Guide', link: '/guide/', activeMatch: '^/guide/' },
      { text: 'Reference', link: '/reference/application', activeMatch: '^/reference/' }
    ],
    sidebar: {
      '/guide/': [
        {
          text: 'Get Started',
          items: [
            { text: 'Introduction', link: '/guide/' },
            { text: 'Installation', link: '/guide/installation' },
          ]
        }
      ],
      '/reference/': [
        {
            text: 'Core',
            items: [
                { text: 'Application', link: '/reference/application' }
            ]
        }
      ]
    },
    footer: {
      message: 'Released under the MIT License.',
      copyright: `Copyright © 2020–${year}`
    },
    socialLinks: [
      { icon: 'github', link: 'https://github.com/vuejs/vitepress' }
    ]
  }
})
