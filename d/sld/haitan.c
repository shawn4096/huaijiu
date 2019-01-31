//haitan.c
//wzfeng
#include <ansi.h>
#include <wanted.h>

inherit ROOM;
int do_kan(string arg);
int go_sld(object me);
int do_yell(string arg);

void create()
{
        set("short", "��̲");
        set("long", @LONG
�����Ƕ���֮����һ��С��̲��������ȥ��һƬ�޼ʵĵ�ãã
�󺣣�Զ������һ�ߣ�������������ֻ��Ÿ�ں��Ϸ��衣��̲����
��ϡϡ�������һЩ��ľ(tree)��
LONG
);

        set("exits", ([
				"southwest" : __DIR__"xiaolu",
            "southeast" : __DIR__"haitan1",
                
        ]));
        set("objects",([
__DIR__"npc/shangren" : 1,
]));
		set ("item_desc", ([
	"tree":"һЩ������Ϊïʢ����ľ������Կ�(chop)��\n",  
	]));
        set("outdoors", "taishan");
        set("coor/x",190);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}

void init()
{
	add_action("do_kan", "chop");
        add_action("do_yell", "yell");
}

int do_kan(string arg)
{
    object me,weapon1,wood;
	

	me=this_player();
	if( !arg || arg=="" ) return 0;
	if(arg!="tree")
		return notify_fail("��Ҫ��ʲô��\n");

	if(!(weapon1=me->query_temp("weapon")))
		return notify_fail("�����û�����������ֿ���\n");
	if(present("mu tou", environment(me)))
				{
					return notify_fail(
"���ﲻ���Ѿ���ľͷ���𣿲�Ҫ���⿳����ľ!!!\n");
				}


	message_vision( HIR "ֻ��$N���һ��������������������$n����Χ����ľ��ȥ ....\n" NOR, me,weapon1);
	message_vision( HIR "ֻ�������ꡱһ������Χ�ļ��ô����ѱ�$N��$n���ɼ���\n"NOR,me,weapon1);
	wood = new(__DIR__"npc/obj/mutou");
	//wood->move(__FILE__);
        wood->move(environment(me));

        return 1;
}

int go_sld(object me)
{
	object hc;
	string str ="ʦ��";
		
	if(!objectp(hc=find_object(__DIR__"hc1")))
		hc=load_object(__DIR__"hc1");
		if(hc->query_temp("curstatus",1)=="run") {
			if(!objectp(hc=find_object(__DIR__"hc2")))
				hc=load_object(__DIR__"hc2");
				if(hc->query_temp("curstatus",1)=="run") {
					if(!objectp(hc=find_object(__DIR__"hc3")))
						hc=load_object(__DIR__"hc3");
						if(hc->query_temp("curstatus",1)=="run")
							return notify_fail("�㺰�˼�����ȴʲô��Ҳû�з�����\n");
                        }
                }
	if(me->query("gender")=="Ů��") str="ʦ��";
	message_vision(CYN"һλСͯ�߹�����$N����һ��˵������λ"+str+"Ҫ��������ô��������������ʱ�ˡ�\n" NOR,me);
	message_vision(CYN"ֻ��һ�Ҵ��Ѿ�ʻ�����ڣ�$N�������˽�ȥ��\n" NOR,me);	
	me->move(hc);
	hc->set_temp("curstatus","run");
	return 1;
}

int do_yell(string arg)
{
	object room, me;
	me = this_player();

	if ( (arg == "������鸣����" || arg == "�������������") && me->query("family/family_name")=="������" ) {
		if ( is_wanted(me) ) return 0;
		else return go_sld(me);
	}

	arg = "��";
	if (me->query("age") < 16  )
		message_vision("$Nʹ�����̵���������һ������" + arg + "��\n", me);
	else if (me->query("neili") > 500)
		message_vision("$N���˿�����һ����" + arg + "������������ƽ�͵�ԶԶ���˳�ȥ��\n", me);
	else
		message_vision("$N������������Хһ������" + arg + "����\n", me);
	
	return 1;
}