#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_me();
void create()
{
        set_name("蓝凤凰", ({ "lan fenghuang", "lan",}));
        set("long", 
"这女子肌肤微黄，双眼极大，黑如点漆。
她掌管日月教在苗疆的下属“五毒教”，
使毒手法诡秘奇特，令人防不胜防。\n");
        set("title",HIY"日月神教  "HIR"五毒圣姑"NOR);
        set("gender", "女性");
        set("age", 20);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
        set("combat_exp", 1000000);

        set_skill("parry",100);
        set_skill("dodge",100);
        set_skill("ding-dodge",100);        
        set_skill("force",100);
        set_skill("huntian-qigong",100);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "huntian-qigong");
	create_family("日月神教",3,"第子");
        set("inquiry", ([
			"迷魂香": (: ask_me :),
		]));
 	set("book_count", 1);


       setup();

	carry_object("/clone/misc/cloth")->wear();        

}
void attempt_apprentice(object ob)
{
	if( (string)ob->query("gender") != "女性" )
	{
		command ("say 对不起，我只收女弟子。");
		return;
	}

        command("say 咦，不错的小女孩嘛，我就收下你了。");
        command("recruit " + ob->query("id"));
        ob->set("title","日月神教五毒圣女");
}



string ask_me()
 {
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "日月神教")
		return RANK_D->query_respect(this_player()) + 
		"与本教素无来往，不知此话从何谈起？";
	if (query("book_count") < 1)
		return "你来晚了，迷魂香不在我处。";
	add("book_count", -1);
	ob = new(__DIR__"obj/yao");
	ob->move(this_player());
	return (RANK_D->query_respect(ob) +"可真坏，可要用在你的心上人身上哦。");
}



