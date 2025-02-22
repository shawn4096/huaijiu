// Room: /d/huashan/siguoya.c
// Date: Look 99/03/25

inherit ROOM;

void quarter_pass();

void create()
{
	set("short", "思过崖");
	set("long", @LONG
这是华山的思过崖。危崖上有个山洞，是华山派历代弟子犯规后囚禁受罚
之所。崖上光秃秃的寸草不生，更无一株树木。这危崖自来自来相传是玉女发
钗上的一颗珍珠，当年华山派的祖师以此危崖为惩罚弟子之所，主要是便此一
处无草无木，无虫无鸟，受罚的弟子在面壁思过之时，不致为外物所扰，心有
旁鹜。
LONG
	);
        set("outdoors", "华山");

	set("exits", ([
	  "eastdown" : __DIR__"xiaolu2",
	  "enter" : __DIR__"hole",
	]));
	set("objects", ([ 
		__DIR__"npc/linghuchong" : 1,
	]));


	set("coor/x",40);
  set("coor/y",50);
   set("coor/z",70);
   setup();
	quarter_pass();
}

void quarter_pass()
{
	mixed *local;

	local = localtime(time() * 60);
	if (local[2] < 6 || local[2] >= 21) {
		set("long", @LONG
这是华山的思过崖。危崖上有个山洞，是华山派历代弟子犯规后囚禁受罚
之所。崖上光秃秃的寸草不生，更无一株树木。天色灰暗，你已看不清四周的
景物。
LONG
		);
		delete("exits/enter");
	}
	else {
		set("long", @LONG
这是华山的思过崖。危崖上有个山洞，是华山派历代弟子犯规后囚禁受罚
之所。崖上光秃秃的寸草不生，更无一株树木。这危崖自来自来相传是玉女发
钗上的一颗珍珠，当年华山派的祖师以此危崖为惩罚弟子之所，主要是便此一
处无草无木，无虫无鸟，受罚的弟子在面壁思过之时，不致为外物所扰，心有
旁鹜。
LONG
		);
		set("exits/enter", __DIR__"hole");
	}
	call_out("quarter_pass", 30);
}

int get_object(object ob)
{
        if(userp(ob))
        return 1;
        return 0;
}

int valid_leave(object me, string dir)
{
    object *inv = deep_inventory(me);
    object *obj;
    obj = filter_array(inv,(:get_object:));
    if( sizeof(obj) && dir =="enter" )
    return notify_fail("你负重过多，行动过于笨拙，脑门一下撞在山壁上。\n");
  if (me->query("fengset") && dir=="enter" )
	{
	me->move(__DIR__"jiabi");
	return notify_fail("你循着高速的捷径一下子进入了夹山壁。\n");
	}
	return ::valid_leave(me, dir);
}
