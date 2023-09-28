VERSION 1.0.1 (2023-09-28)
==========================

- Template project for Windows was separated so there is a distinct template for each MSVC version. CMake's heuristics for detecting the generator seem not to be reliable.
- All rendered triangles are now back-culled, which removes artifacts sometimes present (e.g. dots inside a filled circle). Triangles drawn by `cg::triangle` and `cg::triangle_blend` are reoriented if needed, the function remains orientation-independent.




VERSION 1.0.0 (2023-07-09)
==========================

- First release of cppgraphics library.
