// Sanwu_quest by River@SJ 2001.2.16 
#include <ansi.h>
inherit NPC;

int do_look(string);
int ask_me();
string ask_skill();
string ask_lu();

void create()
{
        object ob;
        set_name("李莫愁", ({ "li mochou", "li", "mochou" }));
        set("long", "她生得极为美貌，但冰冷的目光让人不寒而立。\n");
        set("nickname", "赤练仙子");
        set("gender", "女性");
        set("rank_info/respect", "道姑");
        create_family("古墓派", 3, "弟子");
        set("age", 27);
        set("attitude","heroism");
        set("str", 22);
        set("dex", 23);
        set("con", 20);
        set("int", 24);
        set("shen_type", -1);

        set_skill("parry", 150);
        set_skill("force", 150);
        set_skill("dodge", 150);
        set_skill("sword", 150);
        set_skill("throwing",100);
        set_skill("poison", 50);
        set_skill("meinu-quanfa", 150);
        set_skill("cuff", 150);
        set_skill("meinu-quanfa", 150);       
        set_skill("yunu-shenfa", 150);
        set_skill("yunu-jianfa", 150);
        set_skill("yunu-xinjing", 150);
        map_skill("force", "yunu-xinjing");
        map_skill("dodge", "yunu-shenfa");
        map_skill("cuff", "meinu-quanfa");
        map_skill("sword", "yunu-jianfa");
        prepare_skill("cuff", "meinu-quanfa");
        set("jiali",30);

        set("combat_exp", 1100000);

        set("max_qi", 1700);
        set("max_jing", 1200);
        set("neili", 2500);
        set("max_neili", 2500);

        set("inquiry", ([
            "name" : "站远点！",
            "here" : "我不是本地人，不知道。",
            "情" : "你如何能理解其中相思之苦、惆怅之意？",
            "陆展元" : "你问那个薄情的小畜生做什么？",
            "何沅君" : (: ask_me :),
            "陆无双" : (: ask_lu :),
            "三无三不手" : (: ask_skill :),
            "小龙女" : "那是我的师妹。你问她想干什么？",
            "林朝英" : "那是我的师祖，不该你问的你别问，小心我宰了你。",
        ]));
        
        set("chat_chance", 10);
        set("chat_msg", ({
            "李莫愁纵声而歌，音调凄婉，歌道：「问世间，情是何物，直教生死相许？」\n",
            "李莫愁歌道：「天南地北双飞客，老翅几回寒暑？」\n",
            "李莫愁唱道：「欢乐趣，离别苦，就中更有痴儿女。」\n",
            "李莫愁唱道：「君应有语，渺万里层云，千山暮雪，只影向谁去？」\n",
            "李莫愁词意悲切，声调更是哀怨，唱道：「横汾路，寂寞当年箫鼓。荒烟依旧平楚。」\n",
            "李莫愁歌道：「招魂些何嗟及，山鬼自啼风雨。」\n",
            "李莫愁唱道：「天也妒，未信兴，莺儿燕子俱黄土。」\n",
            "李莫愁唱道：「千秋万古，为留待骚人，狂歌痛饮，来访雁丘处。」\n",
        }) );
        setup();
        if (clonep()) {
                ob = unew(BINGQI_D("sword/zhen"));
                if (!ob) ob = unew(BINGQI_D("changjian"));
                ob->move(this_object());
                ob->wield();
                carry_object(BINGQI_D("bb_zhen"));        
                carry_object("/d/wudang/obj/greenrobe")->wear();
        }       
}

void init()
{
        ::init();
        add_action("do_look","look");
        add_action("do_look","hug");
        add_action("do_look","mo");
        add_action("do_look","18mo");
        add_action("do_look","kiss");
        add_action("do_look","lean");
        add_action("do_look","interest");
        add_action("do_look","flirt");
        add_action("do_look","pretty");
        add_action("do_look","love");
}

int ask_me()
{
        object me;
 
        me = this_player();
        message_vision(
                        HIR "李莫愁冷笑一声：『我这就送你去见她』！\n"
                        "李莫愁决心杀死$N！\n"
                        NOR, me);
        kill_ob(me);
        return 1;
}

string *wheres=({
"/d/emei/xiaowu",               "/d/wudang/xiaolu2",            "/d/xiangyang/zhuquemen",       
"/d/xiangyang/hanshui1",        "/d/jiaxing/nanhu",             "/d/xueshan/xuelu2",
"/d/xueshan/houzidong",         "/d/suzhou/lingyansi",          "/d/suzhou/liuyuan",
"/d/jiaxing/tieqiang",          "/d/hz/longjing",               "/d/hz/huanglongdong",
"/d/hz/yuhuangshan",            "/d/hz/tianxianglou",           "/d/miaojiang/jiedao4",
"/d/foshan/duchang",            "/d/huanghe/shulin5",           "/d/hz/changlang1",
"/d/hz/yuquan",                 "/d/hz/longjing",               "/d/xingxiu/shamo3",
"/d/wudang/xuanyuemen",         "/d/emei/guanyinqiao",          "/d/emei/basipan3",
"/d/tiezhang/shanmen",          "/d/tiezhang/hclu",             "/d/xueshan/huilang4",
"/d/emei/caopeng",              "/d/mingjiao/bishui",           "/d/mingjiao/shanting",
"/d/fuzhou/haigang",            "/d/fuzhou/laozhai",            "/d/xingxiu/shamo2",
"/d/jiaxing/nanhu",             "/d/village/caidi",             "/d/shaolin/songshu2",
"/d/xiangyang/tanxi",           "/d/huashan/husun",             "/d/huashan/yunu",
"/d/mr/xiaojing1-2",            "/d/mr/liulin",                 "/d/suzhou/shihu",
"/d/suzhou/xuanmiaoguan",       "/d/suzhou/zijinan",            "/d/hengshan/cuiping2",
"/d/hengshan/guolaoling",       "/d/shaolin/talin1",            "/d/wudang/husunchou",
"/d/shaolin/shanlu8",           "/d/xueshan/shanlu7",           "/d/foshan/road10",
"/d/foshan/xiaolu2",            "/d/emei/jiulaodong",           "/d/hengshan/beiyuemiao",
"/d/gb/xinglin2",               "/d/gb/shangang",               "/d/fuzhou/zhongxin",
"/d/huanghe/huanghe4",          "/d/huanghe/shamo",             "/d/emei/gudelin3",
});

string ask_skill()
{
        object me = this_player();
        object *obj,ob,room;
        int p,i,y=0;

        if (!me->query("family") 
         ||  me->query("family/family_name") != "古墓派"){
          command("sneer "+ me->query("id"));
          return "这三无三不手如果没有古墓的内功支持，也无法领悟透彻，你学来也无用。";
        }
        if ( me->query_skill("meinu-quanfa", 1) < 120 ){
          command("sneer "+ me->query("id"));
          return RANK_D->query_respect(me) + "的美女拳法还不够熟练，学来也无用。";
        }
        if ( me->query_skill("yinsuo-jinling", 1) < 120 ){
          command("sneer "+ me->query("id"));
          return RANK_D->query_respect(me)+"的银索金铃还不够熟练，学来也无用。";
        }
        if( me->query_temp("limochou/ask") && !wizardp(me))
          return "我不是已经告诉你了么，还不快去帮我找回《五毒秘传》。";
        if(me->query("gmsanwu") && !wizardp(me)){
          command("? " + me->query("id"));
          return "你不是已经学会了三无三不手么？";
        }
        obj = users();
        i = sizeof(obj);
        while(i--) {
            if ( obj[i]->query_temp("limochou/ask")) y++;
        } 
        if(y > 0)
           return "暂时我没有这个兴趣，你回去吧。";

        p = random(sizeof(wheres));
        room= find_object(wheres[p]);
        if(!objectp(room)) return "暂时我没有这个兴趣，你回去吧！";
        ob= new(__DIR__"lu");
        ob->move(room);
        me->set_temp("limochou/ask", 1);
        message_vision(CYN"李莫愁露出一脸的怨恨之色。\n"NOR,me);
        return "我那本《五毒秘传》被陆无双那小贱人给偷走了，如果你能帮我找回此书，我就传授你三无三不手。";
}

int accept_object(object who, object ob,object me)
{
        me= this_object();
        
        if( ob->query("id") != "wudu mizhuan"){
                command("say 你给我这东西干吗？");
                return 0;
        }
        if( ob->query("owner") != who->query("id")
         || !who->query_temp("limochou/ask")){
                command("haha");
                command("say 多谢"+RANK_D->query_respect(who) + "帮忙，小女子多谢了。");
                who->delete_temp("limochou");
                call_out("dest", 1, ob);
                return 1;
        }
        command("say 好吧，那我就传授你三无三不手的心法吧。");
        command("whisper "+ who->query("id")+ " 无孔不入、无所不至、无所不为。");
        who->set("gmsanwu", 1);
        who->delete_temp("limochou");
        call_out("dest", 1 ,ob);
        return 1;
}

void dest(object obj)
{
        if(! obj) return;
        destruct(obj);
}

int do_look(string target)
{
        object me;
 
        me = this_player();
        if (target && present(target, environment()) == this_object()) 
                if ((string)me->query("gender") == "男性") {
                        message_vision(
                                        HIR "李莫愁大怒，喝道：我最恨你们这些薄情的臭男人！去死吧！\n"
                                        "李莫愁决心杀死$N！\n"
                                        NOR, me);
                        command("throw " + me->query("id"));
                        kill_ob(me);
           }
} 

void kill_ob(object me)
{     
      command("haha");
      command("throw bingbo yinzhen at " + me->query("id"));            
      ::kill_ob(me);
}

string ask_lu()
{
	object me, ob, where;
	me=this_player();
	ob = find_living("lu wushuang");
	if (!ob) return "陆无双那小贱人不知道跑哪去了。\n";
	where = environment(ob);
	if (!where) return "陆无双那小贱人不知道跑哪去了。\n";
		return "嗯，陆无双好象出现在"+where->query("short")+CYN"一带。"NOR;
}