// Room: /d/taishan/.c
// Date: CSWORD 96/03/25

inherit ROOM;

void create()
{
        set("short", "玉皇顶");
        set("long", @LONG
此处便是泰山绝顶。这里有一座玉帝观，观前为古登封台，厉
代皇帝封禅的仪式都是在这里举行。台下有一无字碑，据说是汉武
帝所立。不远处有一石碣，上书「孔子小天下处」。正中往上便是
武林盟主所在之处—封禅台。
LONG
        );

        set("exits", ([
                "southdown" : __DIR__"nantian",
                "eastdown" : __DIR__"riguan",
                "west" : __DIR__"zhangren",
                "up" : __DIR__"fengchan",
        ]));
set("objects",([
__DIR__"npc/qinbing1" : 2,
__DIR__"npc/tianmen" : 1
]));
        set("no_clean_up", 1);
        set("outdoors", "taishan");

        set("coor/x",170);
  set("coor/y",220);
   set("coor/z",110);
   setup();
}

void init()
{
      add_action("do_ansuan","ansuan");
}

int do_ansuan()
{
       write("你不能在这里暗算任何人。\n");
       return 1;
}

