inherit ROOM;

void create()
{
        set("short", "正殿");
        set("long",@long
一走进正殿，首先你看到的是号称扬州八怪的画家罗聘所绘寒山，拾得
写意画像石刻和郑文焯指画丰干和尚石刻像。左右碑廊中藏历历代名人岳飞
等题写得诗文，楹联碑刻树方，世传精品。正殿左右的偏殿保存着宋代樟木
雕塑的金身五百罗汉。
long);
set("exits",([
"out" : __DIR__"hanshansi",
"east" : __DIR__"hanshidian",
]));
set("coor/x",50);
  set("coor/y",-200);
   set("coor/z",10);
   setup();
}
