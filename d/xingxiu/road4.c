inherit ROOM;

void create()
{
        set("short", "万里长城");
        set("long", @LONG
这里是万里长城的极西端，城墙高大厚实，上面不时有身穿铠甲的士兵
来回在走动巡逻。往西走便是著名的边关“嘉峪关”，往东通往中原，但必
须先渡过黄河。
LONG);
        set("exits", ([
          "southeast" : __DIR__"road3",
          "west" : __DIR__"fangpan",
        ]));

        set("outdoors", "jyg");

        set("coor/x",-170);
  set("coor/y",70);
   set("coor/z",0);
   setup();
}
