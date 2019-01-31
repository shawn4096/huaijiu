//试剑山庄  gate.c

#include <ansi.h>
#include <room.h>

inherit ROOM;
void create()
{
	set("short",HIY"庄院"NOR);
	set("long", @LONG
眼面的庄院就是名满天下的试剑山庄了，你不觉松了一口气，前往山庄的地
上打扫的一尘不染，汉白玉砌成的台阶豪华典雅，古红木定制的大门紧闭着，使
人无法洞悉门内的一切，三丈多高的琉璃墙在透过树叶的阳光照耀下闪闪发亮，
寂静的四周只闻的远方鸟儿的鸣嘀声。
LONG
	);
        set("exits", ([
		"north" : __DIR__"qianting",
		"out": "/d/city/chmiao",
	]));

	set("no_dig", 1);
        set("no_fight",1);
	set("outdoors", "试剑山庄");
	setup();
}

void init()
{
    object me = this_player();
    tell_object(me,BLINK + HIW"请注意，您已经进入了"HIG"【试剑山庄】"HIR"绝对PK环境"HIW"，生死由命、富贵在天!\n"NOR);
    tell_object(me,BLINK + HIC"当您离开试剑山庄后，系统将会恢复PK保护！\n"NOR);

    if(me->query("no_pk")){
        me->set("no_pk_recover",me->query("no_pk"));
        me->delete("no_pk");
    }
    return;
}

int valid_leave(object me, string dir)
{
	object *ob = deep_inventory(me);
	int i = sizeof(ob);
	if( dir == "out") {
		while (i--)
		if( ob[i]->query("secret_obj"))
			return notify_fail("你带着这么贵重的东西，想离开试剑山庄是不可能的。\n");
	}
        if( dir == "out") {
		if( me->query_condition("killer"))
			return notify_fail("通缉犯必须等探险时间结束才能离开试剑山庄。\n");
	}

        if(dir == "out"){
                if(me->query("no_pk_recover")){
                        tell_object(me,BLINK + HIG"您离开了试剑山庄，系统自动恢复了您的洗手状态！\n"NOR);
                        me->set("no_pk",me->query("no_pk_recover"));
                        me->delete("no_pk_recover");
                }
        me->clear_condition("sjsz_time");
        me->clear_condition("killer");
        me->remove_all_enemy();
        me->remove_all_killer();

    }

	return ::valid_leave(me, dir);
}
