inherit ROOM;

void create()
{
        set("short", "寒拾殿");
        set("long",@long
这里供奉着相传为“和合二仙”化身的寒山，拾得金身塑像，形态生动，
逗人喜爱。寒山寺每年除夕半夜，撞钟一百零八响，其含义是除旧迎新和纪
念佛门一百零八位高僧。
long);
set("exits",([
"out" : __DIR__"fengqiao",
"west" : __DIR__"zhengdian",
]));
set("coor/x",60);
  set("coor/y",-200);
   set("coor/z",10);
   setup();
}
