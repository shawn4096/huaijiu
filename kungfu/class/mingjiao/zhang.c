// zhang.c 张中
// Modify By River@sj 99.06
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_me();
string ask_xunluo();
object ob = this_object();
void create()
{
	set_name("张中", ({ "zhang zhong", "zhang", "zhong" }) );
	set("nickname","铁冠道人");
	set("title", "明教五散人");
	set("gender", "男性");
	set("age",51);
	set("long", "他就是明教五散人之一，人称铁冠道人的张中。\n");
        set("rank_info/respect","道长");
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("shen_type",0);
	set("combat_exp", 600000);
        set("unique", 1);
        set("no_get","张中对你来说太重了。\n");

	set_skill("sword",80);
	set_skill("literate",80);
	set_skill("force",80);
	set_skill("liehuo-jian",85);
	set_skill("dodge",80);
	set_skill("cuff",80);
        set_skill("taizuquan",85);
	set_skill("piaoyi-shenfa",85);
	set_skill("shenghuo-shengong",85);
	map_skill("cuff","taizuquan");
	map_skill("force","shenghuo-shengong");
	map_skill("dodge","piaoyi-shenfa");
	map_skill("sword","liehuo-jian");
	map_skill("parry","liehuo-jian");        
        prepare_skill("cuff", "taizuquan");
        create_family("明教", 36, "散人");
	set("max_qi",1500);
        set("max_jing",1200);
        set("jiali",50);
        set("eff_jingli",1100);
	set("inquiry", ([
                "太极拳经"  : (: ask_me :),
		"秘籍"  : (: ask_me :),
                "画印"  : (: ask_xunluo :),
        ]));

        set("xl", 2);
        set("xl2", "zhang-zhong");
	setup();
        carry_object("/d/mingjiao/obj/yel-cloth")->wear();
	carry_object(BINGQI_D("changjian"))->wield();	
}

#include "5san_app.h";
#include "xunluo.h";

string ask_me()
{
        mapping fam; 
        object ob;
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "明教")
              return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？"; 
        if (this_player()->query_temp("marks/秘1")){
           ob=unew("/d/mingjiao/obj/force_book");
           if(!clonep(ob)) return "你来晚了，太极拳经已给别人拿去了。";
           if(clonep(ob) && ob->violate_unique()){
               destruct(ob);
               return "你来晚了，太极拳经已给别人拿去了。";
           } 
           ob->move(this_player());
           this_player()->delete_temp("marks/秘1");
           return "好吧，既然教主大人已经同意，你就把这本太极拳经拿去吧。\n";
        }
        return "对不起，不经教主同意我不能给你。\n";
}
