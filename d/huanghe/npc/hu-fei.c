inherit NPC;
#include <ansi.h>
int ask_me1();
int ask_me2();

void create()
{
	set_name("���", ({ "hu fei", "hu", "fei" }) );
	set("gender", "����" );
	set("title", HIW"ѩɽ�ɺ�"NOR);
	set("age", 26);
	set("long", 
	    "�ɶ�������һ���Ķ��ӡ�\n");
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
	set("unique", 1);

	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("blade", 300);
	set_skill("cuff",300); 
	set_skill("taxue-wuhen",300);
	set_skill("zhentian-quan",300);
	set_skill("xuantian-wuji",300);
	set_skill("xuanxu-daofa",300);
	map_skill("force","xuantian-wuji");
	map_skill("cuff","zhentian-quan");
	map_skill("dodge","taxue-wuhen");
	map_skill("blade","xuanxu-daofa");
	map_skill("parry","xuanxu-daofa");
	set("combat_exp", 2000000);
	set("max_qi", 3000);
	set("max_jing", 3000);
	set("max_neili", 5000);
	set("eff_jingli",3000);
	set("qi",3000);
	set("jing",3000);
	set("jingli",3000);
	set("neili", 5000);
	set("attitude", "friendly");
	set("inquiry", ([
		"�ҳ�" : (: ask_me1 :),
	]));
	setup();
	set("chat_chance", 2);
	set("chat_msg", ({
		"��쳹��ڷ�ǰ�����ְݡ�\n",
	}) );
	carry_object("/clone/weapon/blade/blade.c")->wield();
	carry_object("/clone/armor/baihu-qiu.c")->wear();
} 

void init()
{
	::init();
	add_action("do_emote","sorry");
}

int ask_me1() 
{
	object me = this_player();
	{
	command("say �����ҵ����ͺųơ���������޵��֡������˷��ڴ˱��䣬���˷��Զ���\n"
"���ҵ�����������������ѳ�򡣴���������ɱ�����ˣ���������ʬ���......������\n"
"�����˺�����ٰ���ྴ���أ����˷���ô������˺��֣�");
	command("consider");
	me->set_temp("marks/ah1",1);
	return 1;
	}
}

int do_emote()
{
	object ob = this_object(); 
	if(this_player()->query("id")=="yan ji") {
	  command("say �ֻ���ԭ������������຦���ҵ�����ȥ���ɣ�");
	  message_vision("$Nһ����$n�����ڵء�\n", ob,present("yan ji"));
	  present("yan ji")->die();
	  command("say ��ȥɱ���Ǹ����ũ��Ϊ��������");
	  message_vision("$N����ææ�뿪�ˡ�\n",ob);
	  destruct(ob);
	  return 1;
	  }
}
