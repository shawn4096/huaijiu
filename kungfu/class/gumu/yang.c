// yang.c 杨过
// By River 98.8
// Modified by darken

string ask_gmjiuyin();

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_sword();
int pfm_haichao();
void create()
{
        set_name("杨过",({"yang guo","yang","guo"}));
        set("title",HIW"古墓侠侣"NOR);
        set("nickname",HIY"神雕大侠"NOR);
        set("long", "他就是名满天下的杨过。虽断一臂但仍遮不去一脸的英雄豪气。\n");
        set("age", 39);
        set("attitude", "friendly");
        set("no_bark",1);
        set("shen", 10000);
        set("per", 30);
        set("str", 40);
        set("int", 30);
        set("con", 40);
        set("dex", 25);

        set("max_qi", 6500);
        set("max_jing", 5000);
        set("neili", 13500);
        set("eff_jingli", 3500);
        set("max_neili", 13500);
        set("jiali", 100);
        set("combat_exp", 2800000);
        set("unique", 1);

        set_skill("sword",300);
        set_skill("dodge",300);
        set_skill("strike",300);
        set_skill("force", 300);
        set_skill("hand", 300);
        set_skill("cuff", 300);
        set_skill("parry", 300);
        set_skill("stick", 300);
        set_skill("staff", 300);
        set_skill("finger",140);
        set_skill("literate", 250);
        set_skill("baituo-shezhang",180);
        set_skill("xiantian-gong",20);
        set_skill("hamagong",300);
        set_skill("medicine",120);
        set_skill("jingmai-xue",80);
        set_skill("qimen-baguazhen",80);
        set_skill("throwing",110);
        set_skill("dagou-bang",220);
        set_skill("bangjue",170);
        set_skill("yuxiao-jian",190);
        set_skill("tanzhi-shentong",160);
        set_skill("yunu-shenfa", 300);
        set_skill("meinu-quanfa",300);
        set_skill("xuantie-jianfa", 300);
        set_skill("anran-zhang", 300);     
        set_skill("quanzhen-jianfa",300);
        set_skill("tianluo-diwang", 300);
        set_skill("yunu-xinjing",300);
        set_skill("jiuyin-zhengong",160);
        set_skill("dafumo-quan",60);
        set_skill("daode-jing",60);
        set_skill("jiuyin-shenfa",130);
        set_skill("qimen-bagua",150);
        set_skill("taoism",100);

        map_skill("force", "yunu-xinjing");        
        map_skill("sword","xuantie-jianfa");
        map_skill("stick","dagou-bang");
        map_skill("staff","baituo-shezhang");
        map_skill("throwing","tanzhi-shentong");
        map_skill("finger","tanzhi-shentong");
        map_skill("dodge", "yunu-shenfa");
        map_skill("parry", "anran-zhang");        
        map_skill("hand", "tianluo-diwang");
        map_skill("cuff", "meinu-quanfa");
        map_skill("strike", "anran-zhang");        
        prepare_skill("strike","anran-zhang");
        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: exert_function, "xinjing" :),
                (: pfm_haichao :),
                (: perform_action, "strike.xiaohun":),
                (: perform_action, "strike.anran":),
        }));
        create_family("古墓派",3,"男主人");
        set_temp("apply/damage", 70);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 60);
        set_temp("apply/armor", 70);
        set("inquiry", ([
           "古墓" : "那日华山与众英雄诀别后和龙儿隐居于此已有数年，不闻世事，能与\n"+
                    "龙儿在此长伴一世，此身足矣！",
           "小龙女" : "龙儿乃我爱妻，你问她做甚？",
           "玄铁剑" : (: ask_sword :),
           "玄铁剑法" : (: ask_sword :),
           "古墓九阴" : (: ask_gmjiuyin :),
        ]));

        setup();
        carry_object(BINGQI_D("sword/gangjian"));
        carry_object("/d/gumu/obj/buxue1")->wear();
        carry_object("/d/gumu/obj/pao1")->wear();
}

void attempt_apprentice(object ob)
{
        mapping fam = ob->query("family");
        if(!fam || fam["family_name"] != "古墓派"){
                command("say "+RANK_D->query_respect(ob)+"与本派素无来往，不知此话从何谈起？");
                return;
        }
        if(ob->query("gender") != "男性") {
                command("bow "+ ob->query("id"));
                command("say 我可只收男徒，你去找吾妻龙儿试试吧。");
                return;
        }       
        if((int)ob->query_skill("yunu-xinjing", 1) < 120) {
                command("say 内功是古墓武功之基础。"); 
                command("say " + RANK_D->query_respect(ob)+"是否还应该先在内功上多下点功夫？");
                return;
        }   
        if((int)ob->query_int() < 32 ) {
                command("say 我的武功都要极高的悟性才能学会。");
                command("say 要能达到炉火纯青之境，体质什么的倒是无关紧要，悟性却是半点也马虎不得。");
                command("say "+RANK_D->query_respect(ob)+"的悟性还大有潜力可挖，还是请回吧。");
                return;
        }
        if((int)ob->query("shen") < 10000){
                command("say 我古墓弟子行走江湖中，一向行侠仗义。");
                command("say 这位" + RANK_D->query_respect(ob)+"正气不够，去做几件侠义的事后再来吧？");
                return;
        }
        command("say 嗯，看你还是个学武的料，我就收下你吧！");         
        command("chat 古墓武功重现江湖，"+ ob->name() +"可别让为师看走眼了！");
        command("chat* pat " + ob->query("id"));
        command("recruit " + ob->query("id"));
        ob->set("title",HIW"古墓派神雕侠侣传人"NOR);
//      ob->set("class","sworder");
}

string ask_sword()
{
        object ob=this_player();
        mapping fam = ob->query("family");
        if ( !fam || fam["family_name"] != "古墓派")
                return RANK_D->query_respect(ob) +"非我古墓传人，不知道此话怎讲？";
        if ( fam["generation"] != 4 )
                return RANK_D->query_respect(ob) +"非我神雕侠侣传人，还是等以后再说吧。";
        if ( ob->query("shen") < -100000)
                return RANK_D->query_respect(ob) +"邪气太重，想必独孤前辈也不愿他的剑法被用来做恶。";
        if ( ob->query("ygpass"))
                return "我不是已经告诉你玄铁剑法的运气之道了么？";
        if ( ob->query("gender")=="男性"){
                command("pat "+ ob->query("id"));
                command("say 当年我在襄阳城南，得遇神雕的相助，于独孤大侠墓前练成玄铁剑法。");
                ob->set("ygpass", 1);
                return "屏气具息，凝气守中，意守丹田，这就是在洪水中运气的诀窍，你好好去领悟一下吧。";
        }
        if ( ob->query("gender") == "女性"){
          if ((int)ob->query_str() < 35 )
                return "这位"+RANK_D->query_respect(ob) +"，玄铁剑法需要极高的膂力，你还是再努力一翻吧。";
          if ((int)ob->query_dex() < 35 )
                return "这位"+RANK_D->query_respect(ob) +"，在洪水中练习玄铁剑法需要极高的身法，你还是再努力一翻吧。";
          if ((int)ob->query_skill("sword", 1) < 200 )
                return "这位"+RANK_D->query_respect(ob) +"的基本剑法还需继续修炼，否则难以抵挡洪水的冲击。";
          if ((int)ob->query_int() < 35 )
                return "这位"+RANK_D->query_respect(ob) +"的悟性还不够高，难以理解我所要讲的口诀。";
          command("pat "+ ob->query("id"));
          command("say 当年我在襄阳城南，得遇神雕的相助，于独孤大侠墓前练成玄铁剑法。");
          ob->set("ygpass", 1);
          return "屏气具息，凝气守中，意守丹田，这就是在洪水中运气的诀窍，你好好去领悟一下吧。";
        }
}

int pfm_haichao()
{
        object me,weapon;
        me = this_object();
        weapon = present("gangjian",me);
        if( me->is_busy()) return 0;
        if( objectp(weapon)){
          set("jiali", 1);
          command("wield jian");
          command("perform haichao");
          if(random(10) > 5){
            set("jiali", 50);
            command("unwield jian");
          }
          return 1;
        }
        else {
          new(BINGQI_D("sword/gangjian"))->move(me);
          set("jiali", 1);
          command("wield jian");
          command("perform haichao");
          if(random(10) > 5){
            set("jiali", 50);
            command("unwield jian");
          }
          return 1;
        }
        return 1;
}

int accept_object(object me, object ob)
{

	if( me->query("family/family_name") == "古墓派"
	&& ob->query("id") == "duanqing dan" && me->query_temp("gmjiuyin")) {
		if(random(10)<6) {
			command("say 这枚丹丸药性不强，实在是派不上用场啊！\n");
			command("sigh " + me->query("id"));
			remove_call_out("destroying");
			call_out("destroying", 1, me, ob);
			return 1;
		}
		command("touch "+me->query("id"));
		command("say 好吧，既然把解药交给了我，那我就将九阴之秘传授于你。\n");
		me->delete_temp("gmjiuyin");
		me->set("gmjiuyin",1); 
		remove_call_out("destroying");
		call_out("destroying", 1, me, ob);
		return 1;
	}

	return 0;
}

string ask_gmjiuyin()
{
	mapping fam;
        int skill;
        skill = this_player()->query_skill("jiuyin-zhengong", 1);

	if ( this_player()->query("gmjiuyin"))
		return RANK_D->query_respect(this_player()) + 
		"你已知晓九阴之玄妙，何来此问？\n";
 
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "古墓派")
		return RANK_D->query_respect(this_player()) + 
		"与本派素无来往，不知此话从何谈起？\n";
	if ( skill < 150 )
		return RANK_D->query_respect(this_player()) + 
		"你的九阴真功太差，无法理解九阴之玄妙。\n";
	if ( present("duanqing dan", this_player()) )
		return RANK_D->query_respect(this_player()) + 
		"既已取得断肠绝情丹，为何不将其交于在下？\n";

	this_player()->set_temp("gmjiuyin");
	return "你若取得断肠绝情丹，在下便为你解答古墓九阴的问题。\n";

}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}