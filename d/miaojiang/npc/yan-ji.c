inherit NPC;
int ask_me();
int ask_me1();

void create()
{
	set_name("�ֻ�", ({ "yan ji", "yan", "ji" }) );
	set("gender", "����" );
	set("title", "��������");
	set("age", 51);
	set("long", 
	    "���ҽ���������ö�������͸¶��һ˿��թ��\n");
	set("str", 20);
	set("dex", 20);
	set("con", 20);
	set("int", 20);
	set("per", 15);
	set("shen_type", 1);
	set("unique", 1);

	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("parry", 150);
	set_skill("unarmed", 150);
	set_skill("huagong-dafa",150); 
//���˸��߼��ڹ���ֻΪ�����ֻ�(Yan ji)��yun qi��
	map_skill("force","huagong-dafa");
	set("combat_exp", 300000);
	set("max_qi", 3000);
	set("max_jing", 1000);
	set("eff_jingli",1000);
	set("max_neili", 2100);
	set("qi",3000);
	set("jing",1000);
	set("jingli",1000);	
	set("neili", 4200);
	set("inquiry", ([
		"��һ��" : (: ask_me :),
		"�¶�"   : (: ask_me1 :),
	]));
	setup();
	set("chat_chance", 2);
	set("chat_msg", ({
		"�ֻ���һ�����о޶����߷�����¨����ٺ١��ļ�Ц������\n",
		"�ֻ�������һ�ۣ�����˵��������Ƽ��ݣ���ˮ���գ��Ƿ񣮣������ȣ�\n",
	}) );
	carry_object("/clone/armor/cloth.c")->wear();
}
 
void init()
{
	::init();
	add_action("do_emote","consider");
}

int ask_me()
{
	object me;
	me = this_player();
	if(me->query_temp("marks/ah1"))
	{
	command("say ��һ�����ǵ���պ������ġ��ɶ���������ƾһ�֡����ҵ���������\n"
"������ֻ��ϧ�������˷�֮����......");
	command("sigh");
	me->set_temp("marks/ah2",1);
	return 1;
	}
}

int ask_me1()
{
	object ob,me;
	me = this_player(); 
	ob = this_object();
	if(me->query_temp("marks/ah2"))
	{
	command("ah");
	command("say ����ô��֪�����ࣿ");
	ob->kill_ob(me);
	me->set_temp("marks/ah3",1);
	return 1;
	}
}

int do_emote(string arg)
{
	object me = this_player();
	object ob = this_object();

	if( !living(ob) && (arg == "yan ji" || arg == "yan" || arg == "ji")) {
	  write("�����ڵ�״���������ܵ������в��\n");
	  return 1;
	  }
	if(me->query_temp("marks/ah3") && (arg == "yan ji" || arg == "yan" || arg == "ji") && (ob=present("hu fei")))
	  {
	  message_vision("$N�����Ƿ�Ҫɱ��$n��\n",me,ob);
	  command("fear");
	  command("say �����ҵ��£������ҵ��°������ǡ����ũ��ָʹС�˸ɵģ�\n���үү����������С���ɡ�����");
	  command("sorry hu");
	  return 1;
	  }
}
