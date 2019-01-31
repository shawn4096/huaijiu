// duan1.c

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("����", ({ "ben chen", "chen", "master" }) );
	set("nickname", "��������ɮ");
	set("gender", "����" );
       	set("class", "bonze");
	set("age", 64);
	set("str", 30);
	set("cor", 27);
	set("cps", 32);
	set("int", 19);
         
	set("max_force", 1500);
	set("force", 1500);
	set("force_factor", 70);

	set("rank_info/respect", "��ɮ");

	set("long", 
	"����λò�����˵ģ�����ͨͨ���Ϻ��С�\n");
	create_family("������", 13, "����");

	set("combat_exp", 1200000);
	set("score", 200000);

	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	(: perform_action, "sword.qian" :)
	}) );

    set_skill("parry", 150);
    set_skill("dodge", 150);
    set_skill("force", 150);
    set_skill("finger", 150);
      set_skill("buddhism", 100);
    set_skill("literate", 100);
    set_skill("duanjia-jianfa",180);
    set_skill("tianlong-shengong", 150);
    set_skill("yiyang-zhi", 150);
    set_skill("lingbo-weibu", 150);

    map_skill("dodge", "lingbo-weibu");
    map_skill("parry", "yiyang-zhi");
    map_skill("finger", "yiyang-zhi");
    map_skill("force", "tianlong-shengong");
    map_skill("sword","duanjia-jianfa");
    prepare_skill("finger","yiyang-zhi");
	set("inquiry", ([
	"name": "ƶɮ���Ǳ���",
	]) );

	setup();
	carry_object(__DIR__ "obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
    if(ob->query_int() < 25)
{
   command("say ѧһ��ָ֮�˱��뵨����ϸ�����ҿ�" + RANK_D->query_respect(ob) + "�������ƺ����ˣ�");
		return;
	}
     if((int)ob->query_skill("buddhism",1)<100)
       {
         command("say �Ҷμ��书���ѧϢϢ��أ��ҿ�"+RANK_D->query_respect(ob)+"��������Ϊ�ƺ�������");
          return;
        }
       if((int)ob->query_skill("tianlong-shengong",1)<100)
        {
          command("say ����һ��ָ�ڹ���Ϊ��Ҫ���ҿ�"+RANK_D->query_respect(ob)+"�ƺ�Ӧ���������϶��µ㹦��");
          return;
        }
	command("smile");
	command("say �ܺã�" + RANK_D->query_respect(ob) + "���Ŭ�������ձض��гɡ�\n");
	command("recruit " + ob->query("id") );
}

void recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class", "swordsman");
}
