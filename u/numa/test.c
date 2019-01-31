// test.c

#include <ansi.h>
inherit ROOM;

mapping *all = ({
	(["party":	"thd",
	  "loc":	({"/d/thd/npc/yaoshi.c",
			"/d/thd/guiyun/npc/lucf.c",
			"/d/thd/guiyun/npc/lugy.c",}),]),

	(["party":	"sl",
	   "loc":	({"/d/shaolin/npc/wumingseng.c",
			"/kungfu/class/shaolin/du-e.c",
			"/kungfu/class/shaolin/du-nan.c",
			"/kungfu/class/shaolin/du-jie.c",}),]),

	(["party":	"em",
	  "loc":	({"/kungfu/class/emei/mie-jue.c",
			"/kungfu/class/emei/fengling.c",
			"/kungfu/class/emei/guhongzi.c",}),]),

	(["party":	"hs",
	  "loc":	({"/d/huashan/npc/feng.c",
			"/d/huashan/npc/yuebuqun.c",
			"/d/huashan/npc/ningzhongze.c",}),]),

    (["party":  "mj",
	  "loc":	({"/kungfu/class/mingjiao/zhangwuji.c",
			"/kungfu/class/mingjiao/fan.c",
			"/kungfu/class/mingjiao/yang.c",}),]),

	(["party":	"mr",
	  "loc":	({"/d/mr/npc/murong-bo.c",
			"/d/mr/npc/murong-fu.c",}),]),

	(["party":	"gm",
	  "loc":	({"/kungfu/class/gumu/yang.c",
			"/kungfu/class/gumu/xln.c",}),]),

	(["party":	"dls",
	  "loc":	({"/kungfu/class/xueshan/jiumozhi.c",
			"/kungfu/class/xueshan/fawang.c",}),]),

	(["party":	"other",
	  "loc":	({"/d/xingxiu/npc/ding.c",
			"/d/songshan/npc/zuo.c",
			"/d/tls/npc/kurong.c",
			"/d/gb/npc/hong.c",
            "/kungfu/class/wudang/zhang.c",
			"/kungfu/class/sld/hant.c",}),]),
});
	
void create()
{
	set("short",RED"武功测试场"NOR);
	set("long","
    这是一间武功测试场，可以随时产生需要的Npc进行测试，具体用
法见说明(show)。\n");
	set("exits",([
               "down" : "/u/numa/workroom",
        ]));
        set("item_desc",([
		"show" : GRN"

		说	明
		
本测试场所用指令为ac <参数>,具体参数为各门派的英文名称缩写。

如：	sl		少林派
	thd		桃花岛
	mr		姑苏慕容
	wd		武当派
	gm		古墓派
	em		峨嵋派
	hs		华山派
	dls		大轮寺
	other		其他派
	all		所有	
	\n"]));
	setup();
}

void init()
{
	object me = this_player();
	if (!wiz_level(me)) return;
	add_action("do_ac","ac");
}

int do_ac(string arg)
{
	object ob,here = this_object();
	mapping which,clone;
    int i,j;
	
	if (!arg)
		return notify_fail("指令格式：ac <门派英文缩写>。\n");
	
	if (arg=="all")
	{
		for (i=0;i<sizeof(all);i++)
		{
			which = all[i];	
			clone = which["loc"];
			for (j=0;j<sizeof(clone);j++)
			{
		        	if( file_size(clone[j]) < 0 )
                		{
                			write(clone[j] + "复制。。。失败。\n");
                			continue;
                		}
                		ob = new(clone[j]);
                		ob->move(here);
                		write(clone[j] + "复制。。。成功。\n");
                	}
                }
                return 1;
        }
        
	for (i=0;i<sizeof(all);i++)
	{
		which = all[i];
		if (arg == which["party"])
		{
			clone = which["loc"];
			for (j=0;j<sizeof(clone);j++)
			{
		        	if( file_size(clone[j]) < 0 )
                		{
                			write(clone[j] + "复制。。。失败。\n");
                			continue;
                		}
                		ob = new(clone[j]);
                		ob->move(here);
                		write(clone[j] + "复制。。。成功。\n");
                	}
        	}
        }
        return 1;
}
