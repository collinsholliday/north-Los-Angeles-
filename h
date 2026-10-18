import * as s3 from '@aws-sdk/client-s3';
import * as cache from '@itchyny/s3-cache-action';

const bucketName: string = 'bucket-name';
const s3Client: s3.S3Client = new s3.S3Client({
  region: process.env.AWS_REGION!,
  credentials: {
    accessKeyId: process.env.AWS_ACCESS_KEY_ID!,
    secretAccessKey: process.env.AWS_SECRET_ACCESS_KEY!,
    sessionToken: process.env.AWS_SESSION_TOKEN!,
  },
});

async function main() {
  const saved = await cache.saveCache(
    ['*.txt'], 'test-key', bucketName, s3Client,
  );
  if (!saved) {
    console.log('Cache already exists, skipped saving.');
  }

  const restoredKey = await cache.restoreCache(
    ['*.txt'], 'test-key', ['test-'], bucketName, s3Client,
  );
  if (restoredKey) {
    console.log(`Cache restored with key ${restoredKey}.`);
  }

  const foundKey = await cache.lookupCache(
    ['*.txt'], 'test-key', ['test-'], bucketName, s3Client,
  );
  if (foundKey) {
    console.log(`Cache found with key ${foundKey}.`);
  }
}