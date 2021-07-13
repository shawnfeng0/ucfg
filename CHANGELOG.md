# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres
to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

[Unreleased]: https://github.com/ShawnFeng0/ucfg/compare/v0.2.0...HEAD

## [0.2.0] - 2021-7-13

[0.2.0]: https://github.com/ShawnFeng0/ucfg/releases/tag/v0.1.0...v0.2.0

### Changed

- Use gcc's `__attribute((__section__()))` attribute to implement the definition of parameter default values, replacing
  the original linked list implementation, so that the reliability of the parameters can be guaranteed before main()
  starts. But it does rely on GCC, at the expense of portability .

## [0.1.0] - 2021-7-12

[0.1.0]: https://github.com/ShawnFeng0/ucfg/releases/tag/v0.1.0

### Added

- Add ucfg library to parse/modify/write back ini format configuration files
- Add ucfg_param library to support convenient management and definition of parameters using function macros
