{
	description = "nix development environment";
	
	inputs = {
		nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
	};

	outputs = { self, nixpkgs }:
		let
			universal = function:
				nixpkgs.lib.genAttrs [
					"x86_64-linux"
					"aarch64-linux"
				] (system: function nixpkgs.legacyPackages.${system});
		in {
			devShell = universal (pkgs: 
				(pkgs.mkShell.override { stdenv = pkgs.llvmPackages_19.libcxxStdenv; } rec {
					name = "quark";

					llvm = "llvmPackages_19";
					clang-tools = pkgs."${llvm}".clang-tools;

					# python for glad binding generation
					python = (pkgs.python312.withPackages (python-pkgs: [
						python-pkgs.jinja2
					]));

					libs = with pkgs; [
						freetype
						libGL
						flac
						libvorbis
						libogg
						udev
						openal
					] ++ (with pkgs.xorg; [
						libX11
						libXrandr
						libXcursor
						libXi
						libXinerama
						libXtst
						libXxf86vm
					]) ++ [
						python
						pkgs."${llvm}".libcxx
					];

					LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath libs;
					buildInputs = libs;

					nativeBuildInputs = with pkgs; [
						git
						
						cmake
						ninja
						
						gdb
						lldb
					] ++ [
						pkgs."${llvm}".clang
						clang-tools
						python
					];

					shellHook = ''
						export PATH="${clang-tools}/bin:$PATH"
						export hardeningDisable=all
					'';
				}));
		};
}
