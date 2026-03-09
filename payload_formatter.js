function decodeUplink(input) {
  var data = {};
  var bytes = input.bytes;
  data.nivel_agua = bytes[0];
  data.nivel_bat = bytes[1];

    return { 
      data: data,
      warnings: [],
      errors: []
  };
}