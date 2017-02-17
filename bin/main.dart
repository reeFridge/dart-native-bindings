import 'dart:io';
import 'package:mpg123bind/src/mpg123bind.dart';

main(List<String> args) {
  stdout.writeln(mpg123_init() == mpg123_error.MPG123_OK);
  stdout.writeln(mpg123_create());
  mpg123_cleanup();
}
