#include <google/protobuf/text_format.h>
#include <glog/logging.h>
#include <leveldb/db.h>

#include <stdint.h>
#include <fstream>  // NOLINT(readability/streams)
#include <string>

#include <iostream>

#include "caffe/proto/caffe.pb.h"
#include "caffe/layers/hdf_data_layer.cpp"

int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}



void convert_dataset(const char* image_filename, const char* label_filename,
                     const char* db_filename) {
    // Open files
    // ...
    
    int rows = 0, cols = 0;
    int num_items = 0;
    
    // read data
    
    // read labels for each data
    
    
    
    // Open leveldb
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    options.error_if_exists = true;
    leveldb::Status status = leveldb::DB::Open(
                                               options, db_filename, &db);
    CHECK(status.ok()) << "Failed to open leveldb " << db_filename
    << ". Is it already existing?";
    
    
    char label;
    char* pixels = new char[rows * cols];
    const int kMaxKeyLength = 10;
    char key[kMaxKeyLength];
    std::string value;
    
    caffe::Datum datum;
    datum.set_channels(1);
    datum.set_height(rows);
    datum.set_width(cols);
    LOG(INFO) << "A total of " << num_items << " items.";
    LOG(INFO) << "Rows: " << rows << " Cols: " << cols;
    for (int itemid = 0; itemid < num_items; ++itemid) {
//        image_file.read(pixels, rows * cols);
//        label_file.read(&label, 1);
        datum.set_data(pixels, rows*cols);
        datum.set_label(label);
        datum.SerializeToString(&value);
        snprintf(key, kMaxKeyLength, "%08d", itemid);
        db->Put(leveldb::WriteOptions(), std::string(key), value);
    }
    
    delete db;
    delete pixels;
}
