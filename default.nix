{ stdenv, avrdude, avrgcclibc }:

stdenv.mkDerivation {
  name = "comms-firmware";
  src = ./.;
  buildInputs = [ avrdude avrgcclibc ];
  installPhase = ''
    install -D -m 0644 comms-firmware.{elf,hex} -t $out
  '';
  dontStrip = true;
  dontPatchELF = true;
}
