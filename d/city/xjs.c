// /d/city/xjs.c
// this is made by beyond
// update 1997.7.5
#include <ansi.h>
inherit ROOM;
void create()
{
         set("short",HIW"小金山"NOR);
         set("long",@long
小金山原名为长春岭，四面环水，山和园林都在湖心的小岛上，山顶筑，
风亭山上植松柏。山东麓墙内有小桂花厅，与之相连的还有一座朝东的花厅，
内有对联一幅：“月来满地水，云起一天山。”
long);
         set("exits",([
         "west" : __DIR__"dhq",
         ]));
	set("outdoors", "扬州");
         set("coor/x",100);
  set("coor/y",30);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",30);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",30);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",30);
   set("coor/z",0);
   setup();
}
