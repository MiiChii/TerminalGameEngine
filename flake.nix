{
  description = "CMake development environment";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = {
    self,
    nixpkgs,
  }: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    devShells = {
      "${system}".default = pkgs.mkShell {
        buildInputs = [
          pkgs.cmake
          pkgs.makeWrapper
          pkgs.gcc
        ];
      };
    };

    packages."${system}".default = pkgs.stdenv.mkDerivation {
      pname = "gameengine";
      version = "unstable";

      src = ./.;

      nativeBuildInputs = [pkgs.cmake pkgs.gcc];
    };
  };
}
