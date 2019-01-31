// NPC: /d/huashan/npc/lingshan.c
// Date: Look 99/03/25

inherit NPC;
string ask_gonglao(object who);


#include <ansi.h>
void create()
{
        set_name("����ɺ", ({ "yue lingshan", "yue", "lingshan" }));
        set("long", 
"��ɽ��������Ⱥ�ͷ���������İ�Ů������������������а����С���ߣ�\n"
"��ɽ�������˽�������Сʦ�á���\n");
        set("nickname", "Сʦ��");
        set("rank_info/respect", "Сʦ��");
        set("gender", "Ů��");
        set("age", 19);
        set("attitude", "peaceful");
        set_max_encumbrance(1000000);
//      set("vendetta_mark", "authority");
        set("shen_type", 1);
        set("str", 22);
        set("int", 25);
        set("con", 23);
        set("dex", 28);
        set("unique", 1);

        set("max_qi",700);
        set("max_jing",600);
        set("neili",600);
        set("max_neili",600);
        set("eff_jingli", 600);
        set("jiali", 20);
        set("combat_exp", 220000);
        set("score", 5000);

        set_skill("sword",  80);
        set_skill("dodge",  80);
        set_skill("unarmed",80); 
        set_skill("force",  80);
        set_skill("parry",  80);
        set_skill("literate",80);
        set_skill("hunyuan-zhang", 80);
        set_skill("strike",80);
        set_skill("huashan-jianfa", 80);
        set_skill("huashan-shenfa", 80);
        set_skill("zixia-gong",80);

        map_skill("force", "zixia-gong");
        map_skill("parry", "huashan-jianfa");
        map_skill("strike", "hunyuan-zhang");
        map_skill("sword", "huashan-jianfa");
        map_skill("dodge", "huashen-shenfa");

        prepare_skill("strike", "hunyuan-zhang");
        create_family("��ɽ��", 14, "����");

        set("inquiry", ([
                "����"  : (: ask_gonglao :),
        ]));


        setup();
	 carry_object(BINGQI_D("sword/sword"))->wield();
	 carry_object(ARMOR_D("armor/cloth"))->wear();
}

void heart_beat()
{
	::heart_beat();

	clear_conditions_by_type("poison");
	if( !is_fighting() && living(this_object()))
		reincarnate();
}

int accept_object(object who, object obj)
{
	int times;
        object ling,me;
        ling = present("ling pai", who);
        me = this_object();

	if ( obj->query("victim_id") != "mengmian ren"
         || !obj->is_corpse()
         && obj->query("id") != "shouji" ) {
                command("say �ⶫ����Ҫ��û�á�");
                return 0;
        }

        if ( !ling )
              return notify_fail("��������أ�\n");
        if ( !who->query_temp("hs/jobji")) 
              return notify_fail("�㻹û����������ô������̳�ˣ�\n");
        if ( (int)ling->query_temp("mmr", 1) != who->query("id") )
              return notify_fail("���������������ưɣ�\n");
        if ( (int)ling->query_temp("done", 1) > 1 )
              return notify_fail("�����ô��������ˣ���Ͻ���ȥ�����ɡ�\n");

        if ( !who->query_temp("hs/have")) 
              return notify_fail("�㻹û��ȥ�Ҷ�������ô������̳�ˣ�\n");

        if ( obj->query("id") == "mengmian ren") {
	if ( obj->query_temp("mmr", 1) != who->query("id") ) 
                return notify_fail("���˺���δ�ڻ�ɽΪ����������\n");
        }

	if ( obj->query_temp("faint_by") != who &&
	     obj->query("kill_by") != who ) 
                return notify_fail("���˺�������ɱ�İɣ�\n");

        if ( obj->query("victim_user") )
                return notify_fail("��������ɻ���أ�û��ô���ף�\n");
	times = ling->query_temp("done", 1);
        write("����ɺ�����������д����һ�� "+CHINESE_D->chinese_number(times+1)+" �֡�\n", who);

        if (!obj->is_corpse() && obj->query("id") != "shouji")
        {
                 command("say " + "�ðɣ���Ѷ������ڼ�̨�������ͷ����ģ�����֮ʿ������֮��ᰲϢ�ˡ�\n");
                  who->set_temp("jitan", 1);
        }
            else
        {
                command("say " + "�һ�ɽ�ɲ�ϲ��ɱ��" + RANK_D->query_respect(who) + "�´β�����˺��¶����ˡ�\n");
	        ling->add_temp("done", 1);
        }
	if( (int)ling->query_temp("done", 1) == 2 )
        	command("say " + "��һ����ʽ��������Ϳ���ȥʦ�����︴���ˡ�\n");
        me->set_max_encumbrance(10000000);
        who->start_busy(random(3));
        who->delete_temp("hs/have");

	call_out("destroying", 1, obj);
        return 1;
}

void destroying(object obj,object me)
{
        if (!obj) return;
        destruct(obj);
        return;
}

void die()
{
	object ob;
	if (!query_temp("living"))
	{
		ob = new("/d/huashan/npc/lingshan");
		ob->move("/d/huashan/jitan");
	}
	::die();
}

string ask_gonglao(object who)
{
        object me;
        int i;
             
        me = this_player();       
        if(!intp(i = me->query("hs_job")))
               return "��ûΪ�һ�ɽ�ɳ����κ�����������ʲô������?"; 

    message_vision("$N��$n˵������Ŀǰ�Ѽǹ�" + chinese_number(i) + "�Ρ�\n",who,me);
        return "�һ�ɽ�������ͷ�����������Ŭ���ɣ�";
}
