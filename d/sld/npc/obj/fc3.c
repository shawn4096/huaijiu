//mu_fa.c
//wzfeng
#include <ansi.h>
inherit ROOM;
void run_mufa(object me);
void run_mufa1(object me);
void run_mufa2(object me);
int do_order(string arg);

void create()
{
        set("short", "С����");
        set("long", @LONG
����һ��С��������û��������ֻ�����ź��˵����������
��ǰƮȥ��ˮ��վ�ڴ�β�����ڵȴ�������
LONG
);
		
        set("exits", ([
                
        ]));
	//set("no_fight",1);
        set("outdoors", "taishan");
        set_temp("curstatus","ready");
        setup();
}
void init()
{
	add_action("do_order", "order");
    
}

int do_order(string arg)
{
 	if( !arg || arg=="" ) return 0;
        if(query_temp("curstatus",1)=="run") return 0;
	if(arg!="����")
	return notify_fail("������ʲô��\n");
	message_vision( HIY "$N�Դ�β��ˮ�ִ��˸����ƣ�˵��������������\n" NOR, this_player());
	message_vision( HIY "ˮ����������緫�������÷���\n"
		"һ�󺣷紵����ֻ��������Ȼ���٣���ǰ��ʻ��ȥ��\n"NOR,this_player());
set("long","����һ��С������������緫��ǰ��ʻ�����ź��˵��������\n"
"���͵�����ҡ�Ρ���β��ˮ�ֺ���Ҳ��Щ��������������һ����С\n"
"�ı�����û��\n");
	
	set("player",this_player()->query("id"));
        set_temp("curstatus","run");
    remove_call_out("run_mufa");
    call_out("run_mufa", 10,this_player());

return 1;	
	
}

void run_mufa(object me)
{
     message("vision","С����ͻȻ����һ�գ�������ǰ��ʻ��ȥ��\n", this_object());
    remove_call_out("run_mufa1");
    call_out("run_mufa1", 6,me);		 

}

void run_mufa1(object me)
{
     message("vision","С��������������ʻ��ȥ���㿴����һ��½�ص�Ӱ�ӡ�\n", this_object());
    remove_call_out("run_mufa2");
    //remove_call_out("run_mufa1");
    //if(random(10)>7)
           call_out("run_mufa2", 6,me);
    /*else		 
      call_out("run_mufa1", 30,me);*/	 

}

void run_mufa2(object me)
{
    object* ob;
    int i;

    message("vision","ֻ��С���������ļ��٣������򰶱�ʻȥ��", this_object());
    //message("vision","�����ˡ�ˮ�ֶ���ߺ��һ��\n", this_object());
    ob = all_inventory(this_object());
    for(i=0; i<sizeof(ob); i++) 
    {
        if(!objectp(ob[i])) continue;
        tell_object(ob[i], "�����ˡ�ˮ�ֶ���ߺ��һ��\n");
        ob[i]->move("/d/sld/haitan");
        message_vision("$N����һԾ�����˴���\n",ob[i]); 
    }
    //message("vision","һ����Ӱ��С��������������\n",me,);
    if(i>0)
    	message("vision","С����������ͷ,����ʻ��󺣡�\n",ob[0]);
    set_temp("curstatus","ready");
}



