// cool980310
// ������
// cool980724
// Modify By River 98/12
inherit NPC;

string ask_duan1();
string ask_duan2();
int checking(object me);
int do_kill(object me, object ob);
void create()
{
        set_name("���ۿ�", ({ "qingpao ke", "ke"}) );
        set("gender", "����" );
        set("age", 52);
        set("str", 26);
        set("con", 23);
        set("dex", 5);
        set("int", 25);
        set("per", 10);
   	set("attitude", "friendly");

        set("max_qi", 7000);
        set("max_jing", 3000);
        set("eff_jingli", 3000);
        set("max_neili", 10000);
	set("qi", 3500);	
        set("max_neili", 4000);
        set("neili", 10000);
        set("jiali", 150);
        set("jiali", 100);
        
        set("long","�����Ǹ����ߣ����봹�أ���Ŀ��ڡ�\n",);
     set("env/һ��ָ","����");
        set("combat_exp", 2000000);
        set("shen", -20000);

        set("chat_chance_combat", 30);
        set("chat_msg_combat",({ 
           (: perform_action, "finger.sandie" :), 
        }));

        set_skill("parry", 210);
        set_skill("dodge", 160);
        set_skill("force", 210);
        set_skill("finger", 220);
        set_skill("buddhism", 100);
        set_skill("literate", 120);
        set_skill("sword", 130);
        set_skill("duanjia-jianfa", 120);
        set_skill("qiantian-yiyang", 210);
        set_skill("yiyang-zhi", 220);
        set_skill("tianlong-xiang", 50);

        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "yiyang-zhi");
        map_skill("finger", "yiyang-zhi");
        map_skill("force", "qiantian-yiyang");
        prepare_skill("finger","yiyang-zhi");

        set("inquiry", ([
            "����" : (: ask_duan2 :),
            "name" : (: ask_duan1 :),
            "������" : (: ask_duan1 :),
        ]));

        setup();
        carry_object("/d/dali/npc/obj/pao")->wear();
}

string ask_duan1()
{
        object me,ob;
        ob=this_player();
        me=this_object();
        me->set_name("������", ({ "duan yanqing", "duan","yanqing"}) );
	me->set("title","�Ĵ����");
        me->set("nickname","�����ӯ");
	ob->set_temp("duanyu/ask1",1);
        return ("�Ϸ�����Ĵ�����е��ϴ󣺶�����!\n");
}

string ask_duan2()
{
        object me,ob;
        ob=this_player();
        me=this_object();
		if( ob->query_temp("duanyu/find2")&& ob->query_temp("duanyu/ask1"))
		   {
		   	command("hehe " + ob->query("id"));
                call_out("do_kill", 1, me, ob);  

           return ("��ȶ�������������!\n");
		   } else return ("���������ʲô��\n");
		

}

int do_kill(object me, object ob)
{
	me->kill_ob(ob);
	ob->fight_ob(me);
	call_out("checking", 0, me); 	
 	return 1;
}

int checking(object me)
{
       object ob;
       ob=this_player();
       if (!ob->query_temp("kill")) {
       if (me->query("qi")*10/me->query("max_qi") < 5 
        || me->query("eff_qi")*10/me->query("max_qi") < 3 ){
	 ob->set_temp("kill",1);
	 message_vision("$n����$N���һ��������һƬ�����֡�\n", me, ob);
	 message_vision("$n�����ȵ��������ܣ�$n����׷�˹�ȥ��\n", me, ob);
	 ob->move("/d/dali/wuliang/shanlin-1");
	 destruct(me);
         }
       else {   
	 call_out("checking", 1, me);
         return 1;
	 }
    }
}
void die()
{
	message_vision("$N��Ц������ɱ���ң��Ⱳ�ӱ����ҵ������ˡ�\n", this_object());
	destruct(this_object());
}
