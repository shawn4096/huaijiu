// dongfang.c ��������

inherit NPC;

inherit F_MASTER;

#include <ansi.h>

string ask_me();
void create()

{
        
	set_name("��������", ({ "dongfang bubai", "dongfang",}));
        
	set("long", 
"����������֮��һλ���춯�أ��������Ĺֽܡ�
�˿�������˺��룬���Ͼ�Ȼʩ��֬�ۣ������Ǽ�����
ʽ���в��У�Ů��Ů����ɫ֮�����㴩����Ů���ϣ�Ҳ
�Ե�̫���ޡ�̫������Щ��\n");
        set("title",HIY"�������  ����"NOR);         
	set("nickname", HIR"�ճ����� Ψ�Ҳ���"NOR);
        set("gender", "����");
        set("age", 24);
        set("attitude", "peaceful");
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);
        set("max_qi", 3000);
	set("qi", 3000);
        set("max_jing", 3000);
	set("jing", 3000);
	set("jingli", 3000);
	set("eff_jingli", 3000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 150);
        set("combat_exp", 1500000);
        set("shen", -150000);

        set_skill("sword", 200); 
        set_skill("parry", 200);
        set_skill("dodge", 200);
        set_skill("claw", 200);
        set_skill("force",200);
        set_skill("pixie-jian",200);        
	set_skill("youming-zhao", 200);
	set_skill("huntian-qigong", 200);

        map_skill("sword", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("dodge", "pixie-jian");
        map_skill("claw", "youming-zhao");
	map_skill("force", "huntian-qigong");

	prepare_skill("claw", "youming-zhao");

        create_family("�������", 1, "����");
/*        set("inquiry", ([
			"��������": (: ask_me :),
	]));
 	set("book_count", 1);*/
        setup();
     
  	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/misc/cloth")->wear();        

}

int do_kill(object ob)
{
	object me = this_object();
        int number,number_t,k_qi,k_neili,k_jing;

// PowerUp
        number = (int)ob->query("max_pot");
        number = number-100;
        k_qi = (int)ob->query("max_qi") + random((int)ob->query("max_qi") / 10 + 500);
        k_jing = (int)ob->query("max_jing");
        k_neili = (int)ob->query("max_neili") + random((int)ob->query("max_qi") / 10 + 500);

        number = (int)(number - random(10));
// ��� skill set
        number_t = number - 10;

//set killer's skill
        me->set_skill("force",number_t + random(15));
        me->set_skill("dodge",number_t + random(15));
        me->set_skill("parry",number_t + random(15));
        me->set_skill("huntian-qigong",number_t + random(15));
        me->set_skill("pixie-jian",number_t + random(15));
        me->set_skill("sword",number_t + random(15));
        me->set_skill("claw",number_t + random(15));
        me->set_skill("youming-zhao",number_t + random(15));
// set killer's  skill maps
        me->map_skill("force","huntian-qigong");
        me->map_skill("dodge","pixie-jian");
        me->map_skill("parry","pixie-jian");
        me->map_skill("sword","pixie-jian");
        me->map_skill("claw","youming-zhao");
// set killer's skill prepares
        me->prepare_skill("claw","youming-zhao");
// copy entire dbase values
        me->set("max_qi",k_qi);
        me->set("eff_qi",k_qi);
        me->set("qi",k_qi);
        me->set("max_jing",k_jing);
        me->set("eff_jing",k_jing);
        me->set("jing",k_jing);
        me->set("max_neili",k_neili);
        me->set("neili",k_neili);
        me->set("combat_exp",ob->query("combat_exp"));
        me->set_temp("skillset",1);	
	me->add_temp("apply/attack", 50 + random(50));

        command("look " + ob->query("id"));
        me->kill_ob(ob);
        call_out("do_run",200,ob);
        return 1;
}

int do_run(object ob)
{
	message_vision("�����������쳤̾�����书��ǿ����Ҳ��������������ˣ�");
	command("escape");
	destruct(ob);
}

void die()
{
        object ob = this_object();
        object me = this_player();
        object pl, ob1, sp;

        me = query_temp("last_damage_from");

        if (me->query_temp("hostage/job_3") != 22) {
                ob->revive(1);
                command("say �ã���Ȼ��" + me->name(1) + "���㣬�һ�������Ϊ���");
                destruct(ob);
                return;
        }

       	ob->revive(1);
       	command("shout");
       	tell_object(me, HIW"�������ܻ�æ�Ӵ��ˣ������е�����һ��������\n"NOR);
       	message_vision("$N��æ���������𣬴����˻��С�\n",me);
       	sp = unew("/d/hj/obj/shoupa");
       	if (!sp)
       		sp=new("/d/hmy/obj/shoupa");
       	sp->move(me);
// Find 3 ZL
	if (pl = find_player(me->query_temp("hostage/partner"))) {
		if (ob1= present("wang zhanglao",environment(pl)) && ob1->is_fighting()) {
			message_vision(HIR"$Nһ�����²����æһ�����У����˹�ȥ����·�Ӵܶ�ȥ��\n"NOR,ob1);
			destruct(ob1);
		}
		if (ob1= present("fan zhanglao",environment(pl)) && ob1->is_fighting()) {
			message_vision(HIR"$Nһ�����²����æһ�����У����˹�ȥ����·�Ӵܶ�ȥ��\n"NOR,ob1);
			destruct(ob1);
		}	
		if (ob1= present("fan zhanglao",environment(pl)) && ob1->is_fighting()) {
			message_vision(HIR"$Nһ�����²����æһ�����У����˹�ȥ����·�Ӵܶ�ȥ��\n"NOR,ob1);
			destruct(ob1);
		}
	}
       	me->set_temp("hostage/win3",me->query_condition("hostage3")*40);
	destruct(ob);
	return;
	        
        ::die();
}

/*
void attempt_apprentice(object ob)
{
	int i = (int)ob->query("shen", 1);
	if( (string)ob->query("gender") != "����" )
	{
		command("say ��......�㻹û���ʸ����ҵ�ͽ�ܡ�");
		return;
	}
	if( i > 0 ) 
	{
		command("grin");
		return;
	}
        command("deadlove " + ob->query("id"));
	command("kiss");
        command("recruit " + ob->query("id"));
        ob->set("title", HIC"������̳���"NOR);
}

string ask_me()
 {
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "�������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";
	if (query("book_count") < 1)
		return "�������ˣ����������Ѿ������Ҵ���";
	add("book_count", -1);
	ob = new(__DIR__"obj/kuihua");
	ob->move(this_player());
	return "�ðɣ��Ȿ���������䡹���û�ȥ�úÿ�����";
}*/
