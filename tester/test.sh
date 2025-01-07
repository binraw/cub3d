#!/bin/bash

path="."
exec="../cub3D"
path_correcte="$path/map_correcte"
path_incorrecte="$path/map_incorrecte"
yellow='\033[33m'
green='\033[32m'
reset='\033[0m'

new_path="."

make -C ./../.
clear

echo -e "$green""Norminette :$reset"
norminette ../libft ../headers ../src | grep -B 1 "Error"

echo -e "$green""====================== Tests Correctes ======================$reset"
echo -e "$yellow""$path_correcte/test_color.cub$reset"
$1 $exec $path_correcte/test_color.cub
echo -e "$yellow""$path_correcte/test_color2.cub$reset"
$1 $exec $path_correcte/test_color2.cub
echo -e "$yellow""$path_correcte/test_color3.cub$reset"
$1 $exec $path_correcte/test_color3.cub
echo -e "$yellow""$path_correcte/test_color4.cub$reset"
$1 $exec $path_correcte/test_color4.cub
echo -e "$yellow""$path_correcte/grande_map.cub$reset"
$1 $exec $path_correcte/grande_map.cub
echo -e "$yellow""$path_correcte/grande_map2.cub$reset"
$1 $exec $path_correcte/grande_map2.cub
echo -e "$yellow""$path_correcte/grande_map3.cub$reset"
$1 $exec $path_correcte/grande_map3.cub
echo -e "$yellow""$path_correcte/grande_map4.cub$reset"
$1 $exec $path_correcte/grande_map4.cub
echo -e "$yellow""$path_correcte/grande_map5.cub$reset"
$1 $exec $path_correcte/grande_map5.cub
echo -e "$yellow""$path_correcte/grande_map6.cub$reset"
$1 $exec $path_correcte/grande_map6.cub
echo -e "$yellow""$path_correcte/grande_map7.cub$reset"
$1 $exec $path_correcte/grande_map7.cub
echo -e "$yellow""$path_correcte/map_nord.cub$reset"
$1 $exec $path_correcte/map_nord.cub
echo -e "$yellow""$path_correcte/map_nord2.cub$reset"
$1 $exec $path_correcte/map_nord2.cub
echo
echo -e "$green""Tests dimensions map$reset"
echo
echo -e "$yellow""$path_correcte/map_démesurée.cub$reset"
$1 $exec $path_correcte/map_démesurée.cub
echo -e "$yellow""$path_correcte/map_démesurée2.cub$reset"
$1 $exec $path_correcte/map_démesurée2.cub
echo -e "$yellow""$path_correcte/map_démesurée_labyrinthe.cub$reset"
$1 $exec $path_correcte/map_démesurée_labyrinthe.cub
echo -e "$yellow""$path_correcte/toute_petite.cub$reset"
$1 $exec $path_correcte/toute_petite.cub

echo
echo -e "$green""=============== Tests format incorrects ====================$reset"
echo
echo -e "$green""Tests nombre fichier incorrect$reset"
echo
$1 $exec $path_correcte/grande_map.cub $path_correcte/grande_map.cub
$1 $exec
echo -e "$green""###############################################$reset"
echo
echo -e "$green""Tests nom fichier incorrect$reset"
echo
echo -e "$yellow""../cub3D not_existing$reset"
$1 $exec not_existing
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D not_existing.cub$reset"
$1 $exec not_existing.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_correcte/nom_incorecte.cub$reset"
$1 $exec $path_correcte/nom_incorecte.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_correcte/nom_incorecte.pdf$reset"
$1 $exec $path_correcte/nom_incorecte.pdf
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/ext_incorrecte.cu$reset"
$1 $exec $path_incorrecte/ext_incorrecte.cu
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/ext_incorrecte.cubf$reset"
$1 $exec $path_incorrecte/ext_incorrecte.cubf
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/ext_incorrecte.cucub$reset"
$1 $exec $path_incorrecte/ext_incorrecte.cucub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/wrong_format.pdf$reset"
$1 $exec $path_incorrecte/wrong_format.pdf

echo
echo -e "$green""================= Tests map incorrectes =====================$reset"
echo
echo -e "$green""Tests règles de générations de map non respectées$reset"
echo
echo -e "$yellow""../cub3D $path_incorrecte/double_perso.cub$reset"
$1 $exec $path_incorrecte/double_perso.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/double_perso2.cub$reset"
$1 $exec $path_incorrecte/double_perso2.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/double_perso3.cub$reset"
$1 $exec $path_incorrecte/double_perso3.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/map_démesurée_sans_perso.cub$reset"
$1 $exec $path_incorrecte/map_démesurée_sans_perso.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/without_perso.cub$reset"
$1 $exec $path_incorrecte/without_perso.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/no_map.cub$reset"
$1 $exec $path_incorrecte/no_map.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/empty.cub$reset"
$1 $exec $path_incorrecte/empty.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/wrong_component.cub$reset"
$1 $exec $path_incorrecte/wrong_component.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/unvalid_space.cub$reset"
$1 $exec $path_incorrecte/unvalid_space.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/unvalid_space2.cub$reset"
$1 $exec $path_incorrecte/unvalid_space2.cub

echo
echo -e "$green""Tests maps non fermées$reset"
echo
echo -e "$yellow""../cub3D $path_incorrecte/opened_map.cub$reset"
$1 $exec $path_incorrecte/opened_map.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/opened_map2.cub$reset"
$1 $exec $path_incorrecte/opened_map2.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/opened_map3.cub$reset"
$1 $exec $path_incorrecte/opened_map3.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/opened_map4.cub$reset"
$1 $exec $path_incorrecte/opened_map4.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/opened_map5.cub$reset"
$1 $exec $path_incorrecte/opened_map5.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/opened_map6.cub$reset"
$1 $exec $path_incorrecte/opened_map6.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/opened_map7.cub$reset"
$1 $exec $path_incorrecte/opened_map7.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/opened_map8.cub$reset"
$1 $exec $path_incorrecte/opened_map8.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/opened_map9.cub$reset"
$1 $exec $path_incorrecte/opened_map9.cub

echo
echo -e "$green""Tests sur les textures ou les couleurs$reset"
echo
echo -e "$yellow""../cub3D $path_incorrecte/same_texture.cub$reset"
$1 $exec $path_incorrecte/same_texture.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/same_texture2.cub$reset"
$1 $exec $path_incorrecte/same_texture2.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/test_color.cub$reset"
$1 $exec $path_incorrecte/test_color.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/test_color2.cub$reset"
$1 $exec $path_incorrecte/test_color2.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/test_color3.cub$reset"
$1 $exec $path_incorrecte/test_color3.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/one_color.cub$reset"
$1 $exec $path_incorrecte/one_color.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/one_texture.cub$reset"
$1 $exec $path_incorrecte/one_texture.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/double_north_texture.cub$reset"
$1 $exec $path_incorrecte/double_north_texture.cub
echo -e "$green""###############################################$reset"
echo -e "$yellow""../cub3D $path_incorrecte/double_weast_texture.cub$reset"
$1 $exec $path_incorrecte/double_weast_texture.cub

echo
echo -e "$green""================= Tests nouvelles maps =====================$reset"
echo
echo -e "$green""MAP INCORRECTES$reset"
echo
echo -e "$yellow""../cub3D $new_path/cub3D/bad/cheese_maze.cub$reset"
$1 $exec $new_path/cub3D/bad/cheese_maze.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/color_invalid_rgb.cub$reset"
$1 $exec $new_path/cub3D/bad/color_invalid_rgb.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/color_missing_ceiling_rgb.cub$reset"
$1 $exec $new_path/cub3D/bad/color_missing_ceiling_rgb.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/color_missing_floor_rgb.cub$reset"
$1 $exec $new_path/cub3D/bad/color_missing_floor_rgb.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/color_missing.cub$reset"
$1 $exec $new_path/cub3D/bad/color_missing.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/color_none.cub$reset"
$1 $exec $new_path/cub3D/bad/color_none.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/file_letter_end.cub$reset"
$1 $exec $new_path/cub3D/bad/file_letter_end.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/filetype_missing$reset"
$1 $exec $new_path/cub3D/bad/filetype_missing
echo
echo -e "$yellow""$new_path/cub3D/bad/map_first.cub$reset"
$1 $exec $new_path/cub3D/bad/map_first.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/map_middle.cub$reset"
$1 $exec $new_path/cub3D/bad/map_middle.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/map_missing.cub$reset"
$1 $exec $new_path/cub3D/bad/map_missing.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/map_only.cub$reset"
$1 $exec $new_path/cub3D/bad/map_only.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/map_too_small.cub$reset"
$1 $exec $new_path/cub3D/bad/map_too_small.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/matrix.cub$reset"
$1 $exec $new_path/cub3D/bad/matrix.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/player_multiple.cub$reset"
$1 $exec $new_path/cub3D/bad/player_multiple.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/player_none.cub$reset"
$1 $exec $new_path/cub3D/bad/player_none.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/player_on_edge.cub$reset"
$1 $exec $new_path/cub3D/bad/player_on_edge.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/sad_face.cub$reset"
$1 $exec $new_path/cub3D/bad/sad_face.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/textures_dir.cub$reset"
$1 $exec $new_path/cub3D/bad/textures_dir.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/textures_duplicates.cub$reset"
$1 $exec $new_path/cub3D/bad/textures_duplicates.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/textures_invalid.cub$reset"
$1 $exec $new_path/cub3D/bad/textures_invalid.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/textures_missing.cub$reset"
$1 $exec $new_path/cub3D/bad/textures_missing.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/textures_none.cub$reset"
$1 $exec $new_path/cub3D/bad/textures_none.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/textures_not_xpm.cub$reset"
$1 $exec $new_path/cub3D/bad/textures_not_xpm.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/wall_hole_east.cub$reset"
$1 $exec $new_path/cub3D/bad/wall_hole_east.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/wall_hole_north.cub$reset"
$1 $exec $new_path/cub3D/bad/wall_hole_north.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/wall_hole_south.cub$reset"
$1 $exec $new_path/cub3D/bad/wall_hole_south.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/wall_hole_west.cub$reset"
$1 $exec $new_path/cub3D/bad/wall_hole_west.cub
echo
echo -e "$yellow""$new_path/cub3D/bad/wall_none.cub$reset"
$1 $exec $new_path/cub3D/bad/wall_none.cub
echo
echo -e "$green""###############################################$reset"

echo
echo -e "$green""MAP CORRECTES$reset"
echo

echo -e "$yellow""$new_path/cub3D/good/creepy.cub$reset"
$1 $exec $new_path/cub3D/good/creepy.cub
echo
echo -e "$yellow""$new_path/cub3D/good/dungeon.cub$reset"
$1 $exec $new_path/cub3D/good/dungeon.cub
echo
echo -e "$yellow""$new_path/cub3D/good/forbidden.cub$reset"
$1 $exec $new_path/cub3D/good/forbidden.cub
echo
echo -e "$yellow""$new_path/cub3D/good/library.cub$reset"
$1 $exec $new_path/cub3D/good/library.cub
echo
echo -e "$yellow""$new_path/cub3D/good/square_map.cub$reset"
$1 $exec $new_path/cub3D/good/square_map.cub
echo
echo -e "$yellow""$new_path/cub3D/good/subject_map.cub$reset"
$1 $exec $new_path/cub3D/good/subject_map.cub
echo
echo -e "$yellow""$new_path/cub3D/good/test_map_hole.cub$reset"
$1 $exec $new_path/cub3D/good/test_map_hole.cub
echo
echo -e "$yellow""$new_path/cub3D/good/test_map.cub$reset"
$1 $exec $new_path/cub3D/good/test_map.cub
echo
echo -e "$yellow""$new_path/cub3D/good/test_pos_bottom.cub$reset"
$1 $exec $new_path/cub3D/good/test_pos_bottom.cub
echo
echo -e "$yellow""$new_path/cub3D/good/test_pos_left.cub$reset"
$1 $exec $new_path/cub3D/good/test_pos_left.cub
echo
echo -e "$yellow""$new_path/cub3D/good/test_pos_right.cub$reset"
$1 $exec $new_path/cub3D/good/test_pos_right.cub
echo
echo -e "$yellow""$new_path/cub3D/good/test_pos_top.cub$reset"
$1 $exec $new_path/cub3D/good/test_pos_top.cub
echo
echo -e "$yellow""$new_path/cub3D/good/test_textures.cub$reset"
$1 $exec $new_path/cub3D/good/test_textures.cub
echo
echo -e "$yellow""$new_path/cub3D/good/test_whitespace.cub$reset"
$1 $exec $new_path/cub3D/good/test_whitespace.cub
echo
echo -e "$yellow""$new_path/cub3D/good/textures_forbidden.cub$reset"
$1 $exec $new_path/cub3D/good/textures_forbidden.cub
echo
echo -e "$yellow""$new_path/cub3D/good/works.cub$reset"
$1 $exec $new_path/cub3D/good/works.cub
echo
echo -e "$green""###############################################$reset"
