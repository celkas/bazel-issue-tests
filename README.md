# bazel-issue-tests

This is a repository to reproduce an error in bazel (see [this issue](https://github.com/bazelbuild/bazel/issues/16208)). The companion-repository [`bazel-issue-sw`](https://github.com/celkas/bazel-issue-sw/) shows no error. This repository will not work though.

Usage:
```
bazel build -c dbg //:mytest
bazel coverage -c dbg --combined_report=lcov --instrumentation_filter="@sw_repo//:funclib" --action_env=COVERAGE_GCOV_OPTIONS=-b //:mytest
# => WARNING: There was no coverage found.
    
genhtml --branch-coverage --output html "$(bazel info output_path)/_coverage/_coverage_report.dat"
# => genhtml: ERROR: no valid records found in tracefile...
```
