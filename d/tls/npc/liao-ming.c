//cool 98.2.17

inherit NPC;
inherit F_MASTER;

string ask_me_wan();
string ask_me_dan();

object ob = this_object();


void create()
{
	set_name("了明禅师", ({
		"liaoming chanshi",
		"liaoming",
		"chanshi",
	}));
	set("long",
		"他是一位身材削瘦的中年僧人，两臂不甚粗壮。身穿 \n"
              "一袭灰布镶边袈裟，两眼湛湛有神，似乎有一身武艺。\n"
	);


 set("nickname", "他心尊者");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");
        set("age", 45);
        set("str", 23);
        set("int", 23);
        set("con", 23);
        set("dex", 25);
        set("max_qi", 1400);
        set("max_jing", 1300);
        set("neili", 1800);
        set("max_neili", 180);
        set("jiali", 70);
        set("combat_exp", 800000);
        set("shen", 8000);

	set_skill("force", 100);
        set_skill("qiantian-yiyang", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("tianlong-xiang", 100);
        set_skill("finger", 100);
        set_skill("sword", 100);
        set_skill("strike", 100);
        set_skill("qingyan-zhang", 100);
        set_skill("yiyang-zhi", 100);
        set_skill("buddhism", 100);
        set_skill("literate", 90);
        map_skill("strike", "qingyan-zhang");
        map_skill("force", "qiantian-yiyang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "yiyang-zhi");
        map_skill("finger",  "yiyang-zhi");
        prepare_skill("finger", "yiyang-zhi");
        create_family("天龙寺", 14, "弟子");    

//

	set("inquiry", ([
//         "雪露丸" :    (: ask_me_wan :),
//        "天龙丹" :    (: ask_me_dan :),
 		"药" :  "本寺灵丹妙药不少，最有名的就是天龙丹和雪露丸",
	]));

	set("wan_count",2+random(2));
	set("dan_count",2+random(2));

       setup();
        carry_object("/d/tls/obj/jiasha1")->wear();
        carry_object("/d/tls/obj/sengxie")->wear();

}

string ask_me_dan()
{
	mapping fam; 
        object ob, me;
                  me = this_player();
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "天龙寺")
		return RANK_D->query_respect(this_player()) + 
		"与本派素无来往，不知此话从何谈起？";

  if ( (int)this_player()->query_condition("medicine" ) > 0 )
		return RANK_D->query_respect(this_player()) + 
		"你是不是刚吃过药，怎么又来要了？ 灵药多吃有害无宜，过段时间再来吧。";

      if ( (int)this_player()->query("max_neili" ) < 300)
		return RANK_D->query_respect(this_player()) + 
		"功力不够，灵药吃了有害无宜，过段时间再来吧。";

  if (  present("tianlong dan", this_player()) || present("xuelu wan", this_player())  )
		return RANK_D->query_respect(this_player()) + 
		"你现在身上不是有颗药丸吗，怎么又来要了？ 真是贪得无餍！";
         if ((int)me->query("max_neili") >= (int)me->query_skill("force")*10)
return RANK_D->query_respect(this_player()) + "怎么老想吃药呢？你武功已经不凡，去打坐提高修为吧。";
	if (query("dan_count") < 1) return "对不起，天龙丹已经被别人要走了。";

         ob = new("/clone/medicine/tianlong-dan");
	ob->move(this_player());

	message_vision("$N获得一颗天龙丹。\n",this_player());
	return "好吧，此丹练之不易，对内力大有好处，你要小心收藏好了。";

}

string ask_me_wan()
{
	mapping fam; 
	object ob;
	
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "天龙寺")
		return RANK_D->query_respect(this_player()) + 
		"与本派素无来往，不知此话从何谈起？";

        if ( (int)this_player()->query_condition("bonze_drug" ) > 0 )
		return RANK_D->query_respect(this_player()) + 
		"你是不是刚吃过药，怎么又来要了？ 灵药多吃有害无宜，过段时间再来吧。";

        if ( (int)this_player()->query("eff_jingli" ) < 200)
		return RANK_D->query_respect(this_player()) + 
		"功力不够，灵药多吃有害无宜，过段时间再来吧。";

	if ( present("tianlong dan", this_player())|| present("xuelu wan", this_player()) )
		return RANK_D->query_respect(this_player()) + 
		"你现在身上不是有颗药丸吗，怎么又来要了？ 真是贪得无餍！";
	if (query("wan_count") < 1) return "对不起，雪露丸已经发完了";

	ob = new(__DIR__"obj/xuelu-wan");
	ob->move(this_player());

//	add("wan_count", -1);

	message_vision("$N获得一颗雪露丸。\n",this_player());
	return "好吧，此药乃我寺秘制而成，习武之人服之大有好处，你要小心收藏。";

}
#include "liao.h";

