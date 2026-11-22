# isaac-kwon.github.io

Personal website of Minjae Isaac Kwon — <https://isaack.dev>

Built with Jekyll on GitHub Pages using the
[Minimal Mistakes](https://github.com/mmistakes/minimal-mistakes) theme as a
`remote_theme` (version pinned in `_config.yml`).

## Local preview

```bash
bundle install
bundle exec jekyll serve
```

## Site-specific overrides of the theme

- `assets/css/main.scss` — base font size override, imports `_sass/custom.scss`
- `_sass/custom/`, `_includes/expand` — collapsible `<details>` blocks
- `_layouts/custom/gplab.html` — GPLAB landing page layout

## Updating the theme

`.github/workflows/theme-update-check.yml` runs weekly and opens an issue
(label `theme-update`) when a newer Minimal Mistakes release exists. The issue
contains the upstream CHANGELOG and the upstream diff of the files this site
mirrors from the theme: `_config.yml` (upstream template + site values),
`_data/ui-text.yml` (verbatim copy) and `assets/css/main.scss`.

To upgrade: bump the version in `remote_theme`, apply the relevant changes to
those files, and confirm post URLs are unchanged after the Pages build.
