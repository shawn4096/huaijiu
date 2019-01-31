// laoda.c

#include <ansi.h>
inherit NPC;

int ask_mwd();

void create()
{
	set_name("���ϴ�", ({ "chuan laoda" }) );
	set("gender", "����" );
	set("age", 42);
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("rank_info/respect", "���ϴ�");
	set("inquiry", ([
		"name": "�Ҿ���������ϴ����Ƕ�����С��硣",
		"rumors": "��˵����ǰ��һֻ���Ա����ܸ����ˣ����ϵĲƱ��������Ǹ��ص�һ��С�����ˡ�",
		"here": "�����Ǹ���Ψһ�ĳ����ɿ��ˡ�",
		"�����": (: ask_mwd :),

	]) );
	setup();
}

int ask_mwd()
{
        object ob, me, hc, *thing;
        int i; 
        me=this_player();
        ob = load_object("/clone/npc/zhong-shentong");

	if( me->query("id") == ob->query("winner") ) {
             command("say �ϣ�����ͨ�����������ʧԶӭ��\n");
             return 1;
        }

        if( me->query_condition("killer") && !wiz_level(me) ) {
             command("say ���ͨ������������ү����ʲô��˼��\n");
             return 1;
        }

        if (!me->query_temp("marks/�´�������2")) {
             command("say ����ү�ӵĴ���������Ȼ��˵���������͹�����ʲô�أ�\n");
             return 1;
        }

        thing = deep_inventory(me);
	i = sizeof(thing);
	while (i--)
	     if (thing[i]->is_character()) {
		   message_vision("���ϴ����һ���������㻹��������ϴ���\n", me);
	           command("knock "+(string)me->query("id"));
		   command("say �����������ɣ�\n");
		   me->add_busy(100 + random(200));
	           return 1;
		} 

       
             
        if(!objectp(hc=find_object(__DIR__"hc1"))) hc=load_object(__DIR__"hc1");
	     
        if(hc->query_temp("curstatus",1)=="run") {
		   if(!objectp(hc=find_object(__DIR__"hc2"))) hc=load_object(__DIR__"hc2");

		   if(hc->query_temp("curstatus",1)=="run") {
			 if(!objectp(hc=find_object(__DIR__"hc3"))) hc=load_object(__DIR__"hc3");
			 if(hc->query_temp("curstatus",1)=="run")
							
                               return notify_fail("���ϴ�����һ̯�������͹������治�ɣ���ֻ��Щ�����������������������ɡ�\n");
                   }
             }

	say("���ϴ�ɴ����۾����Ծ���˵���͹پ�������ү�������ĸ��ˣ�ʧ��ʧ����\n���������ո��˵��󰡣��ϻ��Ͳ�˵�ˣ����ϴ���\n" );
	message_vision(CYN"ֻ��һ�ҿ촬�Ѿ�ʻ���ɿڣ�$N�������˽�ȥ��\n" NOR,me);	
        me->move(hc);
        me->set("dmd_enter_time",time());
        me->apply_condition("dmd_time",90);
        me->delete_temp("dmd/done");
	hc->set_temp("curstatus","run");
        CHANNEL_D->do_channel( this_object(), "rumor",
                sprintf("%s��ʼ�´���������ð���ˣ�", me->name(1)));
	return 1;
}

void kill_ob(object ob)
{
	ob->remove_killer(this_object());
	remove_killer(ob);
	message_vision("���ϴ����$N�������ҵĵ�����Ҳ����Ұ������\n", ob);
	message_vision("$N��æ��Ц���������ң����ҡ���\n", ob);
}
