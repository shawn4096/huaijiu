#include <ansi.h>

inherit ROOM;
string look_leitai();
void create()
{
        set("short", HIY"������"NOR);
        set("long", "������"+MUD_NAME+"��������ű�����̨��̨�¼��������Ը��Ÿ��ɵĹ��ڡ�
Χ������̨��(leitai)����̨(info)���������֣��˴��������У�������
�ȣ�����ͨ�����������������俴̨��\n");
        set("no_fight", 1);
        set("no_sleep_room", 1);
        set("leitai", "/cmds/leitai/leitai2");
        set("exits", ([            
            "out" : "/d/city/leitai",   
            "east" : __DIR__"lt2a", 
            "west" : __DIR__"lt2b",  
            "south" : __DIR__"lt2c",
            "north" : __DIR__"lt2d",   
        ]));      
        set("item_desc",([            
            "leitai" : (: look_leitai :),
            "info" : "\n����Ҫ���ޣ����ô��룺 dalei �� ����\n",
        ]));
        
        set("outdoors", "������̨");  
        setup(); 
}
#include "leitai_fun.h"

void init()
{
	delete_temp("num");
	add_action("do_biwu", ({ "dalei", "����" }));
     	add_action("do_action", ({"dazuo", "tuna", "lian", "learn", "du", "steal", "hit",
                             "kill", "fight", "study", "practice","exercise", "exert",}));
}

int do_biwu()
{
	object me, ob;
	
	me = this_player();
	
	if( me->query("combat_exp") < 100000 ) 
        	return notify_fail("Ҫ����̨���䣬����ʸ񻹲���Щ����ȥ�����ɡ�\n");  
        	
	if (!(ob = find_object(query("leitai"))))
          	ob = load_object(query("leitai"));
        
        if( !ob ) 
        	return notify_fail("������̨û��׼���ã���֪ͨ��ʦ��\n");  
	if( ob->query_temp("leitai") > 1 )
		return notify_fail("�������ڱ����أ����ȵ����Ƿֳ�ʤ����˵�ɡ�\n");  

	message_vision("\n$N�ο���Ⱥ������˵����"+RANK_D->query_self(me)+"�����ޣ�˵�����̨����ȥ��\n", me);
	return ob->load_user(me);
}


