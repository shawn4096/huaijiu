// /d/xiangyang/caiyongmanor.c

inherit ROOM;

void create()
{
	set("short", "蔡邕庄");
	set("long", @LONG
这里以前曾是汉末名人蔡邕所居的庄院，其女蔡文姬亦曾居于此。曹操拒
蜀时曾拜访过这里，如今事过境迁，早已物是而人非了。
LONG
	);
        set("outdoors", "长安");

	set("exits", ([
		"south" : __DIR__"lantian",
		"north" : __DIR__"caiyongtomb",
	]));

	set("coor/x",-10);
  set("coor/y",70);
   set("coor/z",0);
   setup();
}

