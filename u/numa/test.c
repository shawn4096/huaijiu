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
	set("short",RED"�书���Գ�"NOR);
	set("long","
    ����һ���书���Գ���������ʱ������Ҫ��Npc���в��ԣ�������
����˵��(show)��\n");
	set("exits",([
               "down" : "/u/numa/workroom",
        ]));
        set("item_desc",([
		"show" : GRN"

		˵	��
		
�����Գ�����ָ��Ϊac <����>,�������Ϊ�����ɵ�Ӣ��������д��

�磺	sl		������
	thd		�һ���
	mr		����Ľ��
	wd		�䵱��
	gm		��Ĺ��
	em		������
	hs		��ɽ��
	dls		������
	other		������
	all		����	
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
		return notify_fail("ָ���ʽ��ac <����Ӣ����д>��\n");
	
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
                			write(clone[j] + "���ơ�����ʧ�ܡ�\n");
                			continue;
                		}
                		ob = new(clone[j]);
                		ob->move(here);
                		write(clone[j] + "���ơ������ɹ���\n");
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
                			write(clone[j] + "���ơ�����ʧ�ܡ�\n");
                			continue;
                		}
                		ob = new(clone[j]);
                		ob->move(here);
                		write(clone[j] + "���ơ������ɹ���\n");
                	}
        	}
        }
        return 1;
}
