inherit ROOM;

void create()
{
        set("short", "寒山寺");
        set("long",@long
你走出西门约三十里地，就到了枫桥镇，在唐元和年间，有寒山子曾来
此居住，后希迁禅师在冲建寺院时，更名寒山寺。具载，唐开元年间，诗人
张继赴京应试落第，返途舟船停靠枫桥，赋诗一首：“月落乌啼霜满天，江
枫渔火对愁眠，姑苏城外寒山寺，夜半歌声到客船”。从此，诗韵钟声，脍
炙人口，寺因诗而名扬天下。
long);
set("exits",([
 "enter" : __DIR__"zhengdian",
"southeast" : __DIR__"qsgdao5",
]));
set("coor/x",50);
  set("coor/y",-200);
   set("coor/z",0);
   setup();
}
