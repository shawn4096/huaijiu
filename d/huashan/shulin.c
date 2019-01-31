// Room: /d/huashan/shulin.c
// Date: Look 99/03/25

inherit ROOM;

#include <ansi.h>

string* msg1 = ({
	"��Ȼ",
	"ͻȻ",
	"�͵�",
	"�䲻��",
});
string* msg2 = ({
	"��������",
	"�������",
});
string* msg3 = ({
	"�ܳ�",
	"ɱ��",
});
string* msg4 = ({
	"һ�Ѷ���",
	"����",
	"һ����ȥ",
	"��ȥ",
});
string* msg5 = ({
	"��",
	"����",
	"����·",
	"�����·",
});

string* names = ({
	"/d/village/caidi",
	"/d/village/shilu1",
	"/d/village/shilu2",
	"/d/village/shilu3",
	"/d/village/shilu4",
	"/d/village/shilu5",
	"/d/village/shilu6",
	__DIR__"canglong",
	__DIR__"celang1",
	__DIR__"celang2",
	__DIR__"chaoyang",
	__DIR__"husun",
	__DIR__"pubu",
	__DIR__"qianchi",
	__DIR__"qingke",
	__DIR__"shaluo",
	__DIR__"sheshen",
	__DIR__"shulin1",
	__DIR__"shulin2",
	__DIR__"shulin3",
	__DIR__"shulin4",
	__DIR__"yuquan",
	__DIR__"yunu",
	__DIR__"zhenyue",
	__DIR__"shanlu1",
	__DIR__"xiaolu2",
	__DIR__"siguoya",
	__DIR__"baichi",
	__DIR__"laojun",
	__DIR__"houtang",
	__DIR__"celang3",
	__DIR__"celang4",
});

void create()
{
        set("short", "����");
        set("long",@long
�����ǻ�ɽ�����һƬ�����֣������û�к����֣���ǧ��Ҫ�ڴ˵ؾ�
������˵����ǿ����û�����١�ɱ�˵����龭��������
long);
        set("exits",([
        "west" : __DIR__"shulin3",
        "north" : __DIR__"shulin2",
        "east" : __DIR__"shulin1",
    ]));
    set("coor/x",40);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}

void init(object me)
{
        object ob, name1, ling;
        string objwhere;
        me = this_player();
        name1 = me->query("id");
        ling = present("ling pai", me);
        if( ! (present("mengmian ren", environment(me)) ) 
        && (int)me->query_temp("hs/jobji", 1)==1 
        && (int)me->query_temp("hs/have", 1)==0
        && ling
        && (int)ling->query_temp("done", 1) < 2
        && !(ling->query_temp("hsjob") != name1 )
        &&  random(10) > 3 )
        {
        ob=new(__DIR__"npc/mmr");
        objwhere = names[random(sizeof(names))];
        ob->set("long", ob->query("long")+ "�������Ǹղ�����"+me->query("name")+"("+capitalize(me->query("id"))+")���Ƶ��ˡ�\n");
        ob->set_name("������", ({ "mengmian ren", "ren", me->query("id")+"'s mmr" }) );
        ob->move(objwhere);
        ling->move(ob);
        me->set_temp("hs/have", 1);
        ling->set_temp("mmr", name1);
        ob->set_temp("mmr", name1);
        message_vision(HIW "\n" + msg1[random(sizeof(msg1))] +
        	msg2[random(sizeof(msg2))] + 
        	msg3[random(sizeof(msg3))] + "һ��������" +
        	msg4[random(sizeof(msg4))] + 
        	"$N�����ƣ���" HIY + objwhere->query("short") + 
        	HIW + msg5[random(sizeof(msg5))] + "��ȥ��\n" NOR, me);
        }
}
