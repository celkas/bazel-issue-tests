# bazel-issue-tests

## Problem statement

This is a repository to reproduce [an issue in `bazel`](https://github.com/bazelbuild/bazel/issues/16208). The companion-repository [`bazel-issue-sw`](https://github.com/celkas/bazel-issue-sw/) shows no error. This repository will not work though.

Usage:
```
bazel build -c dbg //:mytest
bazel coverage -c dbg --combined_report=lcov --instrumentation_filter="@sw_repo//:funclib" --action_env=COVERAGE_GCOV_OPTIONS=-b //:mytest
```
The second command will fail with `WARNING: There was no coverage found`. Of course, there IS coverage data present. But the data is excluded by the default coverage collector shell script because `bazel`'s clone of the software repository is located below folder `external`. All `external`'s are excluded, which is a good thing, unless the `external` is the SUT and accordingly instrumented.

Thus the following command
```
genhtml --branch-coverage --output html "$(bazel info output_path)/_coverage/_coverage_report.dat"
```
also fails with `genhtml: ERROR: no valid records found in tracefile`.

These problems do not appear if we test this locally in the [`bazel-issue-sw` repository](https://github.com/celkas/bazel-issue-sw/).

## Workaround

There was a solution for this problem in [this pull request](https://github.com/bazelbuild/bazel/pull/16261) but then the feature got removed again from `bazel` `6.0.0` release. As of now as a workaround for this problem, we can use an intermediate version, e.g. `7.0.0-pre.20221102.3`.

Please note that `genhtml` is not able to find the path if we do not create a symlink into the `bazel` execution runtime folder.
Usage:
```
USE_BAZEL_VERSION=7.0.0-pre.20221102.3 bazel build -c dbg //:mytest
USE_BAZEL_VERSION=7.0.0-pre.20221102.3 bazel coverage -c dbg --combined_report=lcov --instrumentation_filter="@sw_repo//:funclib" --action_env=COVERAGE_GCOV_OPTIONS=-b //:mytest
[ -L external ] && rm external
ln -s $(bazel info execution_root)/external external
genhtml --branch-coverage --output html "$(bazel info output_path)/_coverage/_coverage_report.dat"
```
