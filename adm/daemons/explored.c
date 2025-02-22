//      File    :  /adm/daemons/explored.c
//
inherit F_DBASE;

#define SRCH_DIR "/d/"
#include <ansi.h>
#include <explore.h>
#include <dbase.h>
int explore_level = EXPLORE_LEVEL;
int Check_Illgeal_Target(object target);
int Start_Job(object me, object ob);

void create()
{
        set("channel_id", "江湖传闻");
        CHANNEL_D->do_channel( this_object(), "sys", "探险系统已经启动。\n");
//      Start_Job();
}

// 设置杀手技能水平
void Copy_Skill(object me, object ob)
{
        return;
}

mapping *corpse_des = ({
([      "shen"      :     "-1",
        "content"   :     ({
        ([
                 "name" : "黑风双煞",
                 "des"   : "\n你仔细端详了尸首半天，忽然发现尸体的头颅上赫然有五个血洞。\n",
                 "tar" : "你心中一惊：莫不是黑风双煞所为？！赶紧闪呼！！",
        ]),
        ([
                 "name" : "萧远山",
                 "des"   : "\n你仔细端详了尸首半天，只见他脸上肌肉僵硬不动，身手去摸他手掌，但觉颇有凉意，再探他鼻息，早已气绝多时。他胸间吃了人一记掌重手，肋骨齐断，五脏破裂。很显然，此人是突遭重手，顿时毙命。\n",
                 "tar"  : "你心中一惊：莫不是降龙掌的雷霆掌力，哪一个还有如此之威？！",
        ]),}),
]),
([      "shen"      :     "1",
        "content"   :     ({
        ([
                "name"  : "赵半山",
                "des"   : "\n你仔细端详了尸首半天，看来方死不过半个时辰,看起死前来筋骨脱力,竟似被活活累死的一般\n",
                "tar"   : "你心中一惊：莫不是赫赫有名的武当云手所为？！",
        ]),
        ([
                "name"  : "高老者",
                "des"   : "\n你仔细端详了尸首半天，死者脸上红班点点，脸色苍白得骇人。似是被一种奇特内功所为\n",
                "tar"   : "你心中一惊：莫不是名镇天下的紫霞神功的混元无极掌力？！",
        ]),
        }),
]),
});

// 过滤
int Check_Dir(object obj)
{
        int l,k;
        string name, objfile;
        string *banned_dir = ({ "death", "wizard","register", "zjch", "bj"});

        k = sizeof(banned_dir);

        for(l=0;l<k;l++) {
                if(strsrch((string)obj, (string)banned_dir[l])>=0)
                return 0;
        }

        if( sscanf(obj, "%s.", name)== 1)
                return 0;

return 1;
}

int Check_File(object obj)
{
        string name;
        
        if( sscanf(obj, "%s.c", name)!= 1)
                return 0;       
        return 1;
}

string Chinese_Dir(string dir)
{
        switch(dir) {
        case "/d/shaolin/"  : return "少林寺";break;
        case "/d/wudang/"   : return "武当山";break;
        case "/d/city2/"    : return "北京城";break;
        case "/d/bj/"       : return "北京城";break;
        case "/d/gaibang/"  : return "丐帮";break;
        case "/d/murong/"   : return "慕容山庄";break;
        case "/d/wanshou/"  : return "万兽谷";break;
        case "/d/xingxiu/"  : return "西域";break;
        case "/d/yangzhou/" : return "扬州城";break;
        case "/d/city/"     : return "扬州城";break;
        case "/d/gumu/"     : return "古墓幽静";break;
        case "/d/qz/"       : return "终南山";break;
        case "/d/jiaxing/"  : return "嘉兴城";break;
        case "/d/jqg/"      : return "绝情谷";break;
        case "/d/zjch/"     : return "紫禁城";break;
        case "/d/bt/"       : return "白驼山庄";break;
        case "/d/bdao/"     : return "冰火岛";break;
        case "/d/chengdu/"  : return "成都城";break;
        case "/d/diaoyu/"   : return "钓鱼岛";break;
        case "/d/emei/"     : return "峨嵋山";break;
        case "/d/gaochang/" : return "高昌";  break;
        case "/d/guiyun/"   : return "归云庄";break;
        case "/d/hmy/"      : return "黑墓崖";break;
        case "/d/huanggon/" : return "皇宫";  break;
        case "/d/hs/"       : return "华山";  break;
        case "/d/huashan/"  : return "华山";  break;
        case "/d/liaoguo/"  : return "辽国";  break;
        case "/d/mingjiao/" : return "明教";  break;    
        case "/d/mj/"       : return "明教";  break;
        case "/d/quanzhou/" : return "泉州城";break;
        case "/d/shenlong/" : return "神龙岛";break;
        case "/d/taishan/"  : return "泰山";  break;
        case "/d/thd/"      : return "桃花岛";break;
        case "/d/village/"  : return "华山村";break;
        case "/d/xy/"       : return "襄阳城";break;    
        case "/d/xiangyang/": return "襄阳城";break;
        case "/d/dali/"     : return "大理城";break;
        case "/d/wuliang/"  : return "无量山";break;        
        default : return "未知地域";
        }
}

int Check_Npc(object obj)
{
        int i;
        string name;
        string *banned_name= ({ "小和尚","木人","朱聪","白无常","褚万里","平威",
                           "青鬏龟童","黑无常","白髯老人","劁猪将","沈老板",
                           "擂台直播员","当铺老板","蒙面女子","黄真","神秘美容医生"});

        name = obj->query("name");

        if( member_array(name, banned_name)!=-1 ) {
                return 0;
        }

 write(sprintf("%d ",clonep(obj)));
        if( !obj->is_character()
        ||  userp(obj)
        ||  obj->query("race")!="人类" )
                return 0;

return 1;
}

string Get_Dir()
{
        int j;
        mixed *ob;

        ob = get_dir(SRCH_DIR);
        ob = filter_array(ob, (: Check_Dir :));

        j=sizeof(ob);
        j=random(j);

        ob[j]=SRCH_DIR+(string)ob[j]+"/";
        printf("Dir: "+ob[j]+"\n");
        return ob[j];
}


string Get_File(string dir_name)
{
        int max_filter, max, i, k;
        string err;
        mixed *ob;
        object obb;
        mapping exits;
        
        ob = get_dir(dir_name);
        ob = filter_array(ob, (: Check_File :));

        for(i=0;i<sizeof(ob);i++) {
//                      err=catch(call_other(dir_name+(string)ob[i]));
                        err=catch(obb=load_object(dir_name+(string)ob[i]));
                        if (err) continue;
                        obb=load_object(dir_name+(string)ob[i]);
                        if(!objectp(dir_name+(string)ob[i])) continue;
                        exits=obb->query("exits");
                        if(!mapp(exits)) continue;
                        
        }

        i=random(sizeof(ob));
        ob[i]=dir_name+(string)ob[i];

        if(!err && !ob[i]->query("race")
        && ob[i]->query("short")) {
                printf("File: "+(string)ob[i]+"\n");
                return (string)ob[i];
        }
        else return Get_File(dir_name);
}
int Check_Illgeal_Target(object target)
{
        // 禁止死亡对象的NAME相同。
        if(target->query("name") == this_object()->query("last_target"))
                return 0;

        return 1;
}

string Check_Family(string npcfile)
{
        string family;
        family = npcfile->query("title");
        if(!family) family="";
        return family;
}

string Check_Family1(string npcfile)
{
        string family;
        family = npcfile->query("family/family_name");
        if(!family) family="";
        return family;
}

string Get_Npc()
{
        string family, times, npcfile;
        int i, size;
        object target;
        object *living;


        living=filter_array(livings(), (: Check_Npc :));
write(sprintf("%d ",sizeof(livings())));
        size=sizeof(living);
write(sprintf("%d",size));
        i=random(size);

        while(1) {
                target=living[i];
                if( Check_Illgeal_Target(target)) {
                        npcfile=file_name(target);
                        printf("Npc:%s\n", npcfile);
                        return npcfile;
                }
                i++;
                if ( i >= size ) i=0;
                if ( i == size ) break;
        }

}

void get_corpse(string npc_file, string file_name, object me)
{

        int i, k, p;
        object *inv;
        object corpse, room, victim;

        if(!(victim = find_object(npc_file)))
             victim = load_object(npc_file);
        if(!(room = find_object(file_name)))
             room = load_object(file_name);
        corpse = new(EXPLORE_OB);
        corpse->move(file_name);
//      corpse->move("/u/lancy/workroom");
//      corpse->set("dead_message","");
//      corpse->die();        
        corpse->set_name( victim->name(1) + "的尸体", ({ "corpse" }) );
        corpse->set("age", victim->query("age"));
        corpse->set("gender", victim->query("gender"));
        corpse->set("victim_name", victim->name(1));
        corpse->set("victim_id", victim->query("id"));
        corpse->set("victim_exp", victim->query("combat_exp"));
        corpse->set("victim_shen", victim->query("shen"));
        corpse->set_weight( victim->query_weight() );   
        corpse->set_max_encumbrance( victim->query_max_encumbrance() );
//      corpse->move(file_name);
        if( !wizardp(victim) ) {
                inv = all_inventory(victim);
                inv -= ({ 0 });
                i = sizeof(inv);
                while(i--) {
                        if( (string)inv[i]->query("equipped")=="worn" ) {
                                inv[i]->move(corpse);
                                if( !inv[i]->wear() ) inv[i]->move(environment(victim));
                        }
                        else inv[i]->move(corpse);
                }
        }
        corpse->set("long", victim->long(1)
                + "然而，" + gender_pronoun(victim->query("gender")) 
                + "已经死了，只剩下一具尸体静静地躺在这里。\n");        
        
        

        if( (int)me->query("shen") < 0) k=0;
        if( (int)me->query("shen") > 0) k=1;
        p=sizeof(corpse_des[k]["content"]);
        p=random(p);
        corpse->set("corpse_des", corpse->query("long")+corpse_des[k]["content"][p]["des"]);
        
        return;
}

int Start_Job(object me, object ob)
{
        mapping my, tmp_my;
        string dir_name, file_name, chinese_name, npcfile, name, family;
        int exp, num;
        object shashou/*, corpse, room*/;
        object *living;

        seteuid(getuid());

        npcfile = Get_Npc();
        dir_name = Get_Dir();
        file_name = Get_File(dir_name);
        chinese_name = Chinese_Dir(dir_name);
        family = Check_Family(npcfile);
        name = file_name->query("short");
        if( explore_level > EXPLORE_LEVEL ) {
                remove_call_out("Start_Job");
                return 1;
        }
        get_corpse(npcfile, file_name, me);
        this_object()->set("last_target", npcfile->query("name"));
        CHANNEL_D->do_channel( this_object(), "chat", sprintf(HIC"听说 "+HIW + "◤"+ HIY +"%s%s" + HIW + "◢ " + HIC + "前些日子在 " + HIW + "◤%s的%s"+ HIW + "◢"+ HIC + " 丢了性命，哪位英雄能探得究竟，将不胜感激！"NOR, family,npcfile->query("name"),chinese_name,name));
//call_out("Start_Job", 150, this_object());
        return 1;

//      if( exp > 20000 ) {  // exp 大于 20k 就可以做Job

//              shashou = new("/clone/npc/shashou"); // 出现一个杀手

// 开始设置shashou技能水平
//              Copy_Skill(me, ob);
// 结束设置镖头或者镖师的技能水平

//              shashou->set("catch_user_id",me->query("id"));
//              shashou->move(environment(me));

//      }

}

int set_explore(int level)
{
        if( geteuid(previous_object()) != ROOT_UID )
                return 0;
        explore_level = level;
        return 1;
}

