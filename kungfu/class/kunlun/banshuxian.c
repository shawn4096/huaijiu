// bashuxian.c (kunlun)

inherit NPC;
inherit F_MASTER;
string ask_me();

void create()
{
	set_name("班淑娴", ({ "ban shuxian", "ban" }));
	set("title", "昆仑派掌门夫人");
	set("long",
		"她就是昆仑派掌门、名扬江湖的铁琴先生何太冲的夫人。\n"
		"她是一个身材高大的半老女子，头发花白，双目含威，眉心间聚有煞气。\n");
	set("gender", "女性");
	set("age", 44);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 26);
	set("int", 24);
	set("con", 28);
	set("dex", 28);

	set("max_qi", 1500);
	set("max_jing", 1000);
	set("neili", 1200);
	set("max_neili", 1200);
	set("jiali", 50);
	set("combat_exp", 800000);
	set("score", 40000);

    set_skill("literate", 120);
	set_skill("force", 155);
	set_skill("xuantian-wuji", 160);
	set_skill("dodge", 145);
	set_skill("taxue-wuhen", 155);
	set_skill("strike", 60);
	set_skill("kunlun-zhang", 65);
	set_skill("parry", 160);
	set_skill("sword", 170);
	set_skill("leg", 140);
	set_skill("chuanyun-tui", 160);
	set_skill("liangyi-jian", 170);
	set_skill("xunlei-jian", 160);
	set_skill("mantian-huayu", 160);
	set_skill("throwing", 165);

	map_skill("throwing", "mantian-huayu");
	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("leg", "chuanyun-tui");
	map_skill("parry", "liangyi-jian");
	map_skill("sword", "liangyi-jian");
	prepare_skill("leg", "chuanyun-tui");

	create_family("昆仑派", 4, "掌门夫人");
	set("class", "taoist");

		set("inquiry",
		([
			"秘籍" : (: ask_me :),
		]));

	set("book_count", 1);

	setup();
	carry_object("/d/kunlun/obj/sword.c")->wield();
	carry_object("/d/kunlun/obj/pao2.c")->wear();
}

void attempt_apprentice(object ob)
{
/*	 if((int)ob->query("shen")<0){
	 command("say 我昆仑乃是堂堂名门正派，"+RANK_D->query_respect(ob)+
				"的品德实在令人怀疑。");
	 command("say "+RANK_D->query_respect(ob)+
				"还是先回去做点善事吧。");
	 return;
	 }
*/
	 if(ob->query("gender")=="男性"){
	 command("hmm");
	 command("say "+RANK_D->query_respect(ob)+
				"你们这些臭男人我见了就烦，快给我走开！");
	 return;
	 }

          if(ob->query("appren_hezudao", 1) == 1) {
	 command("say 前辈怎敢开这等玩笑，真是折杀做晚辈的了。");
	 return;
	 }
    
	if(ob->query_skill("xuantian-wuji",1)<100){
	 command("hmm");
	 command("say "+RANK_D->query_respect(ob)+
				"你的玄天无极功太差，我可不想收你。");
	 return;
	 }
	 command("say 好吧，以后你就跟我学武功吧，你须得安心学艺，不可乱来。");
	 command("recruit " + ob->query("id"));
}


string ask_me()
{
		  mapping fam;
		  object ob;

		  if (!(fam = this_player()->query("family"))
		 || fam["family_name"] != "昆仑派")
					 return RANK_D->query_respect(this_player()) +
					 "与本派素无来往，不知此话从何谈起？";
		 if(ob->query("gender")=="男性")
        	     	 return "给我走开，我看见你们这些臭男人就烦。";
		  if (query("book_count") < 1)
					 return "你来晚了，本派真经已被你师兄拿走了。";
		  add("book_count", -1);
		  ob = new("/d/kunlun/obj/lyj-book.c");
		  ob->move(this_player());
		  return "先师曾传下来这本「两仪剑心得」，你拿回去好好钻研。";
}


